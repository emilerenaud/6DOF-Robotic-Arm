#include <TMC2130_process.h>

TMC2130_process::TMC2130_process()
{
    _tmc.Init();
}

int TMC2130_process::Rotation(float position, float microstep, int direction)
{
    static bool _once = true;
    float _move;

    if(_hall.Read())
    {
        if(_once == true)
        {
            if(direction == CW)
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

    _move = position - _degree_counter;

    if(_tmc.Rotation(_move, microstep, direction))
    {
        if(direction == CW)
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