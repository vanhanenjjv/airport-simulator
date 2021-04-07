#include "plane.h"

#include <iostream>

Plane::Plane(int flt, int time, Plane_status status) {
  /*
    Post: The Plane data members flt_num, clock_start,
          and state are set to the values of the parameters flt,
          time and status, respectively.
  */
  flt_num = flt;
  clock_start = time;
  state = status;
  std::cout << "Plane number " << flt << " ready to ";
  if (status == arriving)
    std::cout << "land." << std::endl;
  else
    std::cout << "take off." << std::endl;
}

Plane::Plane() {
  /*
    Post: The Plane data members flt_num, clock_start,
          state are set to illegal default values.
  */
  flt_num = -1;
  clock_start = -1;
  state = null;
}

void Plane::refuse() const {
  /*
    Post: Processes a Plane wanting to use Runway, when
          the Queue is full.
  */
  std::cout << "Plane number " << flt_num;
  if (state == arriving)
    std::cout << " directed to another airport" << std::endl;
  else
    std::cout << " told to try to takeoff again later" << std::endl;
}

void Plane::land(int time) const {
  /*
    Post: Processes a Plane that is landing at the specified time.
  */
  int wait = time - clock_start;

  std::cout 
    << time << ": Plane number " << flt_num << " landed after "
    << wait << " time unit" << ((wait == 1) ? "" : "s")
    << " in the takeoff queue." 
    << std::endl;
}

void Plane::fly(int time) const {
  /*
    Post: Process a Plane that is taking off at the specified time.
  */
  int wait = time - clock_start;

  std::cout 
    << time << ": Plane number " << flt_num << " took off after "
    << wait << " time unit" << ((wait == 1) ? "" : "s")
    << " in the takeoff queue." 
    << std::endl;
}

int Plane::started() const {
  /*
    Post: Return the time that the Plane entered the airport system.
  */
  return clock_start;
}
