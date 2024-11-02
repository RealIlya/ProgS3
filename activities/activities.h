#pragma once

#include <algorithm>
#include <vector>

#include "activity.h"

// Get a maximum-size subset of mutually compatible activities.
std::vector<Activity> get_max_activities(
    const std::vector<Activity> &activities);

std::vector<Activity> get_max_activities_slow(
    const std::vector<Activity> &activities);
