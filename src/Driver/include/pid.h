#ifndef PID_H
#define PID_H

typedef struct {
  float kp;
  float ki;
  float kd;
  float limit;
  float prev_error;
  float integral;
} pid;

void initPID(pid *pid, float kp, float ki, float kd, float limit);

float computePID(pid *pid, float target, float measured, float dt);

#endif
