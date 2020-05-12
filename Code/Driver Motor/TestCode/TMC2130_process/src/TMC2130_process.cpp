#include <TMC2130_process.h>

TMC2130_process::TMC2130_process()
{
    _tmc.Init();
}

int TMC2130_process::Rotation(float position, float microstep)
{
    static bool _once = true;
    float _move;

    if((position - _degree_counter) < 0)
    {
        _move = -1 * (position - _degree_counter);
        _direction = CCW;
    }
    else
    {
        _move = position - _degree_counter; 
        _direction = CW;  
    }

    if(_hall.Read())
    {
        if(_once == true)
        {
            if(_direction == CW)
                _rotation++;
            else
                _rotation--;
            _once = false;
        }
        else
        {
            _once = true;
        }
    }

    if(_tmc.Rotation(_move, microstep, _direction))
    {
        if(_direction == CW)
            _degree_counter += (int)_move;
        else
            _degree_counter -= (int)_move;
        return DONE;
    }
    return NOT_DONE;
}


int TMC2130_process::Homing(float microstep)
{

    if(_tmc.Rotation(_degree_counter, microstep, CCW))  //Returns 1 when done
    {
        _degree_counter = 0;
        return DONE;
    }

    return NOT_DONE;

    // while (!_hall.Read())
    // {
    //   _tmc.Rotation(1, microstep, CCW);  
    // }
}

void TMC2130_process::Disable(void)
{
    _tmc.Endis(HIGH);
}