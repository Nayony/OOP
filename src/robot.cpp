#include "robot.h"

Robot::Robot(int _max_hp, int _max_energy, int _xp_to_lvlup,int _damage, bool _is_enemy, int max_speed)
            :_hp(_max_hp), _max_hp(_max_hp), _energy(_max_energy), _max_energy(_max_energy),
            _xp(0), _xp_to_lvlup(_xp_to_lvlup), _current_lvl(0), _damage(_damage),
            _max_speed(max_speed), _speed(max_speed), _id(-1), _position(0, 0), _is_enemy(_is_enemy),_ability_point(1),
            _can_use_ability(true), _shield(0), _can_move(true), _demise(false)
            {
            }
    void Robot ::SetHp(int value){
        if (value>_max_hp){
            _hp = _max_hp;
        }
        else if (value>0){
            _hp = value;
            }
        if (value <= 0){
            _hp = 0;
        }
    }
    void Robot::AddHp(int value){
        _hp += value;
        if (_hp > _max_hp){
            if (GetShield() != 0){
                AddShield(_hp-_max_hp);
            }
            _hp = _max_hp;
        }
        if (_hp < 0){
            _hp = 0;
        }
    }
    void Robot::SetPos(const Position& position){
        _position = position;
    }
    void Robot::SetId(int id){
        _id = id;
    }
    void Robot ::SetEnergy(int value){
        if (value>_max_energy){
            _energy = _max_energy;
        }
        else if (value < 0){
            _energy = 0;
        }
        else if (value>=0){
            _energy = value;
        }
    }
    void Robot::AddEnergy(int value){
        _energy += value;
        if (_energy > _max_energy){
            _energy = _max_energy;
        }
        if (_energy < 0){
            _energy = 0;
        }
    }
    void Robot ::SetSpeed(int value){
        if (value < 0){
            _speed = 0;
        }
        else if (value > _max_speed){
            _speed = _max_speed;
        }
        else{
            _speed = value;
        }
    }
    void Robot::AddSpeed(int value){
        _speed += value;
        if (_speed > _max_speed){
            _speed = _max_speed;
        }
        if (_speed < 0){
            _speed = 0;
        }
    }
    void Robot::AddDamage(int value){
        _damage += value;
    }
    void Robot::AddShield(int value){
        _shield += value;
        if (_shield < 0){
            _shield = 0;
        }        
    }
    void Robot::ResetSpeed(){
        _speed = _max_speed;
    }
    void Robot::ResetTurnResources(){
        _energy = _max_energy;
        _speed = _max_speed;
    }
    void Robot::IncreaseMaxHp(int value){
        _max_hp += value;
    }
    void Robot::ProcessLevelUps(){
        while (_xp >= _xp_to_lvlup){
            _xp -= _xp_to_lvlup;
            _current_lvl += 1;
            _ability_point += 1;
            IncreaseMaxHp(RobotSettings::MaxHpPerLevel);
            AddHp(RobotSettings::CurrentHpPerLevel);
        }
    }
    void Robot::AddXp(int value){
        if (value>0){
            _xp += value;
        }
        if (_xp >= _xp_to_lvlup){
            ProcessLevelUps();
        }
    }
    void Robot ::SetEnemy(bool value){
        _is_enemy = value;
    }
    void Robot ::SetDemise(bool value){
        _demise = value;
    }
    Abilities* Robot::FindAbility(AbilityType type){
        auto it = std::find_if(_abilities.begin(), _abilities.end(),
                            [type](const std::unique_ptr<Abilities>& ability) { return type == ability->GetAbilityType(); });
        if (it == _abilities.end()) return nullptr;
        else { return it->get();}
    }
    const Abilities* Robot::FindAbility(AbilityType type) const{
        auto it = std::find_if(_abilities.begin(), _abilities.end(),
                            [type](const std::unique_ptr<Abilities>& ability) { return type == ability->GetAbilityType(); });
        if (it == _abilities.end()) return nullptr;
        else { return it->get();}
    }
    void Robot::AddAbility(std::unique_ptr<Abilities> ability)
    {
        _abilities.push_back(std::move(ability));
    }
    void Robot::AddStatus(std::unique_ptr<Statuses> status)
    {
        
        _statuses.push_back(std::move(status));
    }
    void Robot::AddAbilityPoint(int value){ 
        _ability_point += value;
    }
    void Robot::SetCanUseAbility(bool value){ 
        _can_use_ability = value;
    }
    void Robot::SetCanMove(bool value){ 
        _can_move = value;
    }
    Statuses* Robot::FindStatus (StatusType type){
        auto it = std::find_if(_statuses.begin(), _statuses.end(),
                            [type](const std::unique_ptr<Statuses>& status) { return type == status->GetStatusType();});
        if (it == _statuses.end()) return nullptr;
        else { return it->get();}
    }
    void Robot::EraseStatus(StatusType type){
    const auto it = std::find_if(_statuses.begin(), _statuses.end(),
        [type](const std::unique_ptr<Statuses>& s){ return s->GetStatusType() == type; });
    if (it != _statuses.end()) _statuses.erase(it);
}
            
    const int Robot::HasAbilityPoint() const {return _ability_point;}
    const int Robot ::GetDamage() const { return _damage;}
    const int Robot ::GetHp() const { return _hp;}
    const int Robot ::GetMaxHp() const { return _max_hp;}
    const bool Robot ::GetType() const { return _is_enemy;}
    const int Robot ::GetEnergy() const { return _energy;}
    const int Robot ::GetLvl() const { return _current_lvl;}
    const int Robot ::GetXp() const { return _xp;}
    const int Robot ::GetShield() const { return _shield;}
    const int Robot ::GetSpeed() const { return _speed;}
    const int Robot ::GetXpToLvlUp() const { return _xp_to_lvlup;}
    const bool Robot::GetDemise() const{ return _demise;}
    const Position Robot::GetPos() const { return _position; }
    int Robot::GetId() const { return _id; }
    const std::vector<std::unique_ptr<Abilities>>& Robot::GetAbilities() const { return _abilities; }
    const std::vector<std::unique_ptr<Statuses>>& Robot::GetStatuses() const { return _statuses; }
    const bool Robot::CanUseAbility() const{ return _can_use_ability;}
    const bool Robot::CanMove() const{ return _can_move;}
    
