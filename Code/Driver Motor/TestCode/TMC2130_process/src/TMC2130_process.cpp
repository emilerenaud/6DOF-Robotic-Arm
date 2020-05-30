#include <TMC2130_process.h>

TMC2130_process::TMC2130_process()
{
    _tmc.Init();
}

int TMC2130_process::Rotation(float position, float microstep)
{
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
    static bool home_yet = false;
    if(_tmc.Rotation(_degree_counter, microstep, CCW))  // Returns 1 when done
    {
        _degree_counter = 0;
        home_yet = true;
    }

    if(home_yet == true)
    {
        if(_hall.Read())
        {
            _debug.open_green();
            delay(300);
            _debug.close_green();
            home_yet = false;
            return DONE;
        }   
        _tmc.Rotation(2, microstep, CCW);
    }

    return NOT_DONE;
}

void TMC2130_process::Disable(void)
{
    _tmc.Endis(HIGH);
}