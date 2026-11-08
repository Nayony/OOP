#include "map.h"
#include "position.h"
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <random>
#include <vector>

Map::Map(int _w, int _h, int _count_of_blocked)
    : _width(_w), _height(_h), _count_of_blocked(_count_of_blocked) {
  if (_width < MapSettings::MinWidth) {
    _width = MapSettings::MinWidth;
  } else if (_width > MapSettings::MaxWidth) {
    _width = MapSettings::MaxWidth;
  }
  if (_height < MapSettings::MinHeight) {
    _height = MapSettings::MinHeight;
  } else if (_height > MapSettings::MaxHeight) {
    _height = MapSettings::MaxHeight;
  }
  if (_count_of_blocked > std::min(_width, _height) - 1) {
    _count_of_blocked = std::min(_width, _height) - 1;
  }
  _grid.assign(_height, std::vector<Cell>(_width, Cell(false, false, 1)));
}

const std::vector<int> Map::GetSize() const { return {_width, _height}; }
const std::vector<std::vector<Cell>> &Map::GetGrid() const { return _grid; }
std::vector<int> Map::RandomBlockedCells(std::vector<int> &indexes) {
  std::vector<int> nums;
  int value;
  static std::random_device rd;
  static std::mt19937 gen(rd());
  for (int i = 0; i < _count_of_blocked; i++) {
    std::uniform_int_distribution<> distr(0, (int)indexes.size() - 1);
    value = indexes[distr(gen)];
    auto pi = std::find(indexes.begin(), indexes.end(), value);
    if (pi != indexes.end()) {
      indexes.erase(pi);
    }
    nums.push_back(value);
  }
  return nums;
}
std::vector<int> Map::RandomCellsWithStatus(std::vector<int> &indexes) {
  std::vector<int> nums;
  int max_statuses_count = MapSettings::MaxStatusesOnCell;
  int value;
  static std::random_device rd;
  static std::mt19937 gen(rd());
  while (max_statuses_count > 0) {
    std::vector<int> idx_copy = indexes;
    for (int i = 0; i < _count_of_blocked; i++) {
      std::uniform_int_distribution<> distr(0, (int)idx_copy.size() - 1);
      value = idx_copy[distr(gen)];
      auto pi = std::find(idx_copy.begin(), idx_copy.end(), value);
      if (pi != idx_copy.end()) {
        idx_copy.erase(pi);
      }
      nums.push_back(value);
    }
    max_statuses_count--;
  }
  for (int i = 0; i < nums.size(); i++) {
    auto pi = std::find(indexes.begin(), indexes.end(), nums[i]);
    if (pi != indexes.end()) {
      indexes.erase(pi);
    }
  }
  return nums;
}
Cell &Map::GetCell(const Position &position) {
  return _grid[position.Y()][position.X()];
}
Cell &Map::GetCell(Position &position) {
  return _grid[position.Y()][position.X()];
}
const Cell &Map::GetCell(const Position &position) const {
  return _grid[position.Y()][position.X()];
}

bool Map::HasStatus(const Position &position) const {
  if (position.X() < 0 || position.Y() < 0 || position.X() >= _width ||
      position.Y() >= _height)
    return false;
  return GetCell(position).GetStatusesCount() > 0;
}

bool Map::IsAvailable(const Position &pos) const {
  if (pos.X() < 0 || pos.Y() < 0 || pos.X() >= _width || pos.Y() >= _height)
    return false;
  return IsFree(pos) && !IsOccupied(pos);
}

bool Map::HasFreeNeighbor(int x, int y) const {
  if (IsAvailable({x - 1, y}) || IsAvailable({x + 1, y}) ||
      IsAvailable({x, y - 1}) || IsAvailable({x, y + 1})) {
    return true;
  }
  return false;
}

void Map::FindFreeCell(Robot &robot) {
  const bool from_end = robot.GetType();
  const int step = from_end ? MapSettings::EnemySearchStride : 1;
  const int start_x = from_end ? _width - 1 : 0;
  const int start_y = from_end ? _height - 1 : 0;

  for (int y = start_y; y >= 0 && y < _height; y += step) {
    for (int x = start_x; x >= 0 && x < _width; x += step) {
      const Position position(x, y);
      if (!IsAvailable(position) || HasStatus(position) ||
          !HasFreeNeighbor(x, y))
        continue;

      robot.SetPos(Position(x, y));
      _grid[y][x].SetOccupied(true);
      return;
    }
  }
}

    

bool Map::IsAreaAvailable(const Position &main) const {
  for (int dy = 0; dy < MapSettings::FactorySize; ++dy) {
    for (int dx = 0; dx < MapSettings::FactorySize; ++dx) {
      const Position position(main.X() - dx, main.Y() - dy);
      if (!IsAvailable(position) || HasStatus(position))
        return false;
    }
  }
  return true;
}

void Map::MarkFactoryArea(const Position &main) {
  for (int dy = 0; dy < MapSettings::FactorySize; ++dy)
    for (int dx = 0; dx < MapSettings::FactorySize; ++dx)
      _grid[main.Y() - dy][main.X() - dx].SetFactory(true);
}

bool Map::CellsForFactory(Factory &factory) {
  const int size = MapSettings::FactorySize;
  // тут подумать над тем как статус доделать
  for (int y = _height - 1; y >= size - 1; --y) {
    for (int x = _width - 1; x >= size - 1; --x) {
      const Position main(x, y);
      if (!IsAreaAvailable(main))
        continue;

      factory.SetPosMain(main);
      MarkFactoryArea(main);
      return true;
    }
  }
  return false;
}

std::optional<Position> Map::FindFreeAround(const Position &anchor, int size,
                                            int step) const {
  for (int dy = 0; dy < size; dy += step) {
    for (int dx = 0; dx < size; dx += step) {
      Position pos(anchor.X() + 1 - dx, anchor.Y() + 1 - dy);
      if (IsAvailable(pos) && !HasStatus(pos))
        return pos;
    }
  }
  return std::nullopt;
}

std::optional<Position> Map::FindFreeNear(const Factory &factory) const {
  return FindFreeAround(factory.GetPosMain(), MapSettings::FactoryRingSize,
                        MapSettings::FactoryRingStep);
}

std::optional<Position> Map::FindFreeNear(const Robot &robot) const {
  return FindFreeAround(robot.GetPos(), MapSettings::RobotRingSize,
                        MapSettings::RobotRingStep);
}
bool Map::IsFree(const Position &position) const {
  if (position.X() < 0 or position.Y() < 0 or position.X() >= _width or
      position.Y() >= _height) {
    return false;
  }
  if (_grid[position.Y()][position.X()].GetCost() ==
      CellSettings::ImpassableCost) {
    return false;
  }
  return true;
}
bool Map::IsOccupied(const Position &position) const {
  if (!IsFree(position))
    return false;
  if (_grid[position.Y()][position.X()].GetOccupied() == true) {
    return true;
  }
  return false;
}
void Map::AddStatusToCell(Cell &cell) {
  if (cell.GetStatuses().size() == StatusesSettings::MaxStatusesCount)
    return;
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, static_cast<int>(StatusType::sNone) -
                                               1);
  StatusType status = static_cast<StatusType>(distr(gen));
  while (cell.FindStatus(status) != false) {
    status = static_cast<StatusType>(distr(gen));
  }
  cell.AddStatus(status);
}
std::vector<std::vector<Cell>> Map::CreateGrid() {
  _grid.assign(_height, std::vector<Cell>(_width, Cell(false, false, 1)));

  std::vector<int> all_indexes;
  all_indexes.reserve(_width * _height);
  for (int i = 0; i <= _width * _height - 1; ++i) {
    if (_grid[(i / _width)][(i % _width)].GetCost() == 1)
      all_indexes.push_back(i);
  }

  auto blocked = RandomBlockedCells(all_indexes);
  auto costly = RandomBlockedCells(all_indexes);
  auto gotStatus = RandomCellsWithStatus(all_indexes);

  for (int i = 0; i < _height; ++i) {
    for (int j = 0; j < _width; ++j) {
      const int cell_index = i * _width + j;

      if (std::find(blocked.begin(), blocked.end(), cell_index) !=
          blocked.end()) {
        _grid[i][j] = Cell(false, false, CellSettings::ImpassableCost);
      } else if (std::find(costly.begin(), costly.end(), cell_index) !=
                 costly.end()) {
        _grid[i][j] = Cell(false, false, CellSettings::DifficultMoveCost);
      } else {
        _grid[i][j] = Cell(false, false, CellSettings::DefaultMoveCost);
      }
      auto pi = std::find(gotStatus.begin(), gotStatus.end(), cell_index);
      while (pi != gotStatus.end()) {
        AddStatusToCell(_grid[i][j]);
        gotStatus.erase(pi);
        pi = std::find(gotStatus.begin(), gotStatus.end(), cell_index);
      }
    }
  }

  return _grid;
}
int Map::ManhattanDistance(const Position &position1,
                           const Position &position2) const {
  return std::abs(position1.X() - position2.X()) +
         std::abs(position1.Y() - position2.Y());
}
std::vector<Position> Map::CellsInRadius(const Position &center, int radius,
                                         bool enemyNeeded) const {
  std::vector<Position> result;
  for (int y = center.Y() - radius; y <= center.Y() + radius; ++y) {
    for (int x = center.X() - radius; x <= center.X() + radius; ++x) {
      const Position pos(x, y);
      if (enemyNeeded) {
        if (IsFree(pos) && pos != center &&
            ManhattanDistance(center, pos) <= radius)
          result.push_back(pos);
      } else {
        if (IsAvailable(pos) && pos != center &&
            ManhattanDistance(center, pos) <= radius)
          result.push_back(pos);
      }
    }
  }
  return result;
}
std::vector<Position> Map::Dijkstra(Position start, Position end) {
  std::vector<std::pair<int, int>> movement_vector = {
      {1, 0}, {0, -1}, {-1, 0}, {0, 1}};
  auto idx = [&](Position pos) { return pos.Y() * _width + pos.X(); };

  auto idxToPos = [&](int idx) -> Position {
    return {idx % _width, idx / _width};
  };

  auto path = [&](std::vector<int> prev) -> std::vector<Position> {
    std::vector<Position> res;
    int curr_idx = idx(end);

    while (curr_idx != -1) {
      if (curr_idx != idx(start))
        res.push_back(idxToPos(curr_idx));
      curr_idx = prev[curr_idx];
    }

    std::reverse(res.begin(), res.end());
    return res;
  };
  const int N = _width * _height;
  const int INF = 1'000'000;
  std::vector<int> dist(N, INF); // Это минимальный путь в вершину с индексом
  std::priority_queue<std::pair<int, Position>> q;
  std::vector<int> prev(N, -1); // Это откуда мы пришли
  dist[idx(start)] = 0;
  q.push({0, start});
  while (!q.empty()) {
    auto cur = q.top();
    int cur_dist = -cur.first;
    q.pop();
    if (cur.second == end) {
      return path(prev);
    }
    for (auto move : movement_vector) {
      Position npos = {cur.second.X() + move.first,
                       cur.second.Y() + move.second};
      if (IsAvailable(npos) or npos == end) {
        auto new_cell = GetCell(npos);
        if (dist[idx(cur.second)] + new_cell.GetCost() < dist[idx(npos)]) {
          dist[idx(npos)] = dist[idx(cur.second)] + new_cell.GetCost();
          prev[idx(npos)] = idx(cur.second);
          q.push({-dist[idx(npos)], npos});
        }
      }
    };
  }
  return {};
}

void Map::SetVisibleToCells(const Player &player) {
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      if (ManhattanDistance(Position(x, y), player.GetPos()) <=
          player.GetVisibleRadius()) {
        _grid[y][x].SetVisible(true);
        _grid[y][x].SetExplored(true);
      } else {
        _grid[y][x].SetVisible(false);
      }
    }
  }
}
