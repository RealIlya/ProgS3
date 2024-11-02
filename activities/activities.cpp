#include "activities.h"

using namespace std;

int check(vector<bool> *arr, const vector<Activity> &activities) {
  bool t = true;
  int i = 0, finish = 0, res = 0;
  for (; t && i < arr->size(); ++i) {
    if (arr->at(i)) {
      if (finish <= activities[i].start) {
        res++;
        finish = activities[i].finish;
      } else
        t = false;
    }
  }
  return (t) ? res : -1;
}

int recursive(vector<bool> *arr, const vector<Activity> &activities, int i) {
  if (i == arr->size()) {
    return check(arr, activities);
  } else {
    vector<bool> *narr = new vector<bool>(*arr);
    narr->at(i) = true;
    int n1 = recursive(arr, activities, i + 1),
        n2 = recursive(narr, activities, i + 1);
    if (n2 > n1) {
      for (int j = i; j < arr->size(); ++j) arr->at(j) = narr->at(j);
    }
    delete narr;
    return max(n1, n2);
  }
}

vector<Activity> brute_force(const vector<Activity> &activities) {
  vector<Activity> cpyact(activities);
  sort(cpyact.begin(), cpyact.end());
  vector<bool> arr(cpyact.size());
  unsigned int n = recursive(&arr, cpyact, 0);
  vector<Activity> res(n);
  for (int i = 0, j = 0; i < arr.size() && j < n; ++i) {
    if (arr[i]) res[j++] = cpyact[i];
  }
  return res;
}

vector<Activity> fast_algorithm(const vector<Activity> &activities) {
  vector<Activity> cpyact(activities), result, answer;
  sort(cpyact.begin(), cpyact.end());
  int m = 0;
  for (int i = 0; i < cpyact.size(); i++) {
    int current = i, next = current;
    result.clear();
    while (current < cpyact.size()) {
      result.push_back(cpyact[current]);
      next = current;
      for (; cpyact[next].start < cpyact[current].finish; next++);
      current = next;
    }
    if (result.size() > answer.size()) answer = result;
  }
  return answer;
}

vector<Activity> get_max_activities(const std::vector<Activity> &activities) {
  // Function must return a maximum-size subset of mutually compatible
  // activities. Each activity is described by its start and finish times:
  // [start, finish), 0 <= start < finish. Activities are compatible if their
  // time intervals don't overlap. Activities may be given in unsorted order and
  // the result may not be sorted too.
  // return brute_force(activities);
  return fast_algorithm(activities);
}

vector<Activity> get_max_activities_slow(
    const std::vector<Activity> &activities) {
  // Function must return a maximum-size subset of mutually compatible
  // activities. Each activity is described by its start and finish times:
  // [start, finish), 0 <= start < finish. Activities are compatible if their
  // time intervals don't overlap. Activities may be given in unsorted order and
  // the result may not be sorted too.
  return brute_force(activities);
  // return fast_algorithm(activities);
}
