#include "pid.h"

void initPID(pid *pid, float kp, float ki, float kd, float limit) {
  pid->kp = kp;
  pid->ki = ki;
  pid->kd = kd;
  pid->limit = limit;
  pid->prev_error = 0.0f;
  pid->integral = 0.0f;
}

float computePID(pid *pid, float target, float measured, float dt) {
  float error = target - measured;

  pid->integral += error * dt;
  if (pid->integral > pid->limit)
    pid->integral = pid->limit;
  if (pid->integral < -pid->limit)
    pid->integral = -pid->limit;

  float derivative = (error - pid->prev_error) / dt;
  pid->prev_error = error;

  float output =
      (pid->kp * error) + (pid->ki * pid->integral) + (pid->kd * derivative);

  if (output > pid->limit)
    output = pid->limit;
  if (output < -pid->limit)
    output = -pid->limit;

  return output;
}
