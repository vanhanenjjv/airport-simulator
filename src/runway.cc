#include "runway.h"

#include <iostream>

Runway::Runway(int limit) {
  /*
    Post: The Runway data members are initialized to record no
          prior Runway use and to record the limit on queue sizes.
  */
  queue_limit = limit;
  num_land_requests = num_takeoff_requests = 0;
  num_landings = num_takeoffs = 0;
  num_land_refused = num_takeoff_refused = 0;
  num_land_accepted = num_takeoff_accepted = 0;
  land_wait = takeoff_wait = idle_time = 0;
}

Error_code Runway::can_land(const Plane &current) {
  /*
    Post: If possible, the Plane current is added to the
          landing Queue; otherwise, an Error_code of overflow is
          returned. The Runway statistics are updated.
    Uses: class Extended_queue.
  */
  Error_code result;

  if (landing.Size() < queue_limit)
    result = landing.Append(current);
  else
    result = fail;
  num_land_requests++;

  if (result != success)
    num_land_refused++;
  else
    num_land_accepted++;

  return result;
}

Error_code Runway::can_depart(const Plane &current) {
  /*
    Post: If possible, the Plane current is added to the
          takeoff Queue; otherwise, an Error_code of overflow is
          returned. The Runway statistics are updated.
    Uses: class Extended_queue.
  */
  Error_code result;

  if (takeoff.Size() < queue_limit)
    result = takeoff.Append(current);
  else
    result = fail;
  num_takeoff_requests++;
  if (result != success)
    num_takeoff_refused++;
  else
    num_takeoff_accepted++;

  return result;
}

Runway_activity Runway::activity(int time, Plane &moving) {
  /*
    Post: If the landing Queue has entries, its front
          Plane is copied to the parameter moving
          and a result  land is returned. Otherwise,
          if the takeoff Queue has entries, its front
          Plane is copied to the parameter moving
          and a result  takeoff is returned. Otherwise,
          idle is returned. Runway statistics are updated.
    Uses: class Extended_queue.
  */
  Runway_activity in_progress;

  if (!landing.IsEmpty()) {
    landing.Retrieve(moving);
    land_wait += time - moving.started();
    num_landings++;
    in_progress = land;
    landing.Serve();
  }
  else if (!takeoff.IsEmpty()) {
    takeoff.Retrieve(moving);
    takeoff_wait += time - moving.started();
    num_takeoffs++;
    in_progress = Runway_activity::takeoff;
    takeoff.Serve();
  }
  else {
    idle_time++;
    in_progress = idle;
  }

  return in_progress;
}

void Runway::shut_down(int time) const {
  /*
    Post: Runway usage statistics are summarized and printed.
  */
  std::cout 
    << "Simulation has concluded after " << time << " time units." << std::endl
    << "Total number of planes processed "
    << (num_land_requests + num_takeoff_requests) << std::endl
    << "Total number of planes asking to land "
    << num_land_requests << std::endl
    << "Total number of planes asking to take off "
    << num_takeoff_requests << std::endl
    << "Total number of planes accepted for landing "
    << num_land_accepted << std::endl
    << "Total number of planes accepted for takeoff "
    << num_takeoff_accepted << std::endl
    << "Total number of planes refused for landing "
    << num_land_refused << std::endl
    << "Total number of planes refused for takeoff "
    << num_takeoff_refused << std::endl
    << "Total number of planes that landed "
    << num_landings << std::endl
    << "Total number of planes that took off "
    << num_takeoffs << std::endl
    << "Total number of planes left in landing queue "
    << landing.Size() << std::endl
    << "Total number of planes left in takeoff queue "
    << takeoff.Size() << std::endl;
  std::cout 
    << "Percentage of time runway idle "
    << 100.0 * (( float ) idle_time) / (( float ) time) << "%" << std::endl;
  std::cout 
    << "Average wait in landing queue "
    << (( float ) land_wait) / (( float ) num_landings) << " time units";
  std::cout 
    << std::endl << "Average wait in takeoff queue "
    << (( float ) takeoff_wait) / (( float ) num_takeoffs)
    << " time units" << std::endl;
  std::cout 
    << "Average observed rate of planes wanting to land "
    << (( float ) num_land_requests) / (( float ) time)
    << " per time unit" << std::endl;
  std::cout 
    << "Average observed rate of planes wanting to take off "
    << (( float ) num_takeoff_requests) / (( float ) time)
    << " per time unit" << std::endl;
}
