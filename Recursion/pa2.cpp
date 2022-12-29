#include <iostream>
#include <cstring>
#include "cleaning_robot.h"
using namespace std;

/*
   *    COMP 2011 2021 Fall Programming Assignment 2
   *    Student Name        : Li Chun Tak
   *    Student ID          : 20791241
   *    Student ITSC email  : ctliaj@connect.ust.hk
   * 
   * You are not allowed to use extra library
*/

// Please do all your work in this file. You just need to submit this file.

int findMaximumPlace(int robot_x, int robot_y, int robot_energy, int robot_full_energy, 
   char result_map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH]) {

   int reachable = 0;

   if (result_map[robot_y][robot_x] == 'B' || robot_y < 0 || robot_x < 0 || robot_y >= MAP_HEIGHT || robot_x >= MAP_WIDTH) {
      return 0;
   }

   if (result_map[robot_y][robot_x] == 'C') {
      result_map[robot_y][robot_x] = ' ';
      reachable += findMaximumPlace(robot_x, robot_y, robot_full_energy, robot_full_energy, result_map, temp_map);
   }

   if (result_map[robot_y][robot_x] != 'V') {
      // printMap(result_map);
      reachable++;
      // cout << robot_x << " " << robot_y << " return: " << reachable << endl;
   }
   
   result_map[robot_y][robot_x] = 'V';

   if (robot_energy <= 0) {
      robot_energy++;
      
      return reachable;
   }

   reachable += findMaximumPlace(robot_x, robot_y-1, robot_energy-1, robot_full_energy, result_map, temp_map);

   reachable += findMaximumPlace(robot_x+1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map);

   reachable += findMaximumPlace(robot_x, robot_y+1, robot_energy-1, robot_full_energy, result_map, temp_map);

   reachable += findMaximumPlace(robot_x-1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map);

   //debug
   // cout << "positionNum: " << reachable << endl;

   return reachable;
}

int findShortestDistance(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, 
   int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH]) {
   
   int distance = PA2_MAX_PATH;

   // if target is in B or out of bound
   if (map[target_y][target_x] == 'B' || target_y < 0 || target_y >= MAP_HEIGHT || target_x < 0 || target_y >= MAP_WIDTH) {
      return distance;
   }

   // for debugging
   // cout << "x: " << robot_x << " y: " << robot_y << " energy: " << robot_energy << endl;

   if (map[robot_y][robot_x] == 'B' || robot_y < 0 || robot_x < 0 || robot_y >= MAP_HEIGHT || robot_x >= MAP_WIDTH) {
      return distance;
   }

   int temp;
   int d = robot_full_energy - robot_energy + 1;
   
   if (robot_x == target_x && robot_y == target_y) {
      return d;
   }

   if (map[robot_y][robot_x] == 'C' && temp_map[robot_y][robot_x] != 'X') {
      temp_map[robot_y][robot_x] = 'X';
      temp = findShortestDistance(robot_x, robot_y, target_x, target_y, robot_full_energy, robot_full_energy, map, temp_map);
      // cout << "distance added: " << temp -1 + d << " current distance: "<< distance << endl;
      if (temp != PA2_MAX_PATH) {
         if (temp-1+d < distance) {
            // cout << "distance added: " << temp -1 + d << " current distance: "<< distance << " x: "<< robot_x << " y: " << robot_y << endl;
            distance = temp-1+d;
         }
      }
      temp_map[robot_y][robot_x] = '\0';
   }


   if (robot_energy <= 0) {
      robot_energy++;
      return distance;
   }

   temp = findShortestDistance(robot_x, robot_y-1, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
   if (temp != PA2_MAX_PATH) {
      if (temp < distance) {
         distance = temp;
      }
   }

   temp = findShortestDistance(robot_x+1, robot_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
   if (temp != PA2_MAX_PATH) {
      if (temp < distance) {
         distance = temp;
      }
   }

   temp = findShortestDistance(robot_x, robot_y+1, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
   if (temp != PA2_MAX_PATH) {
      if (temp < distance) {
         distance = temp;
      }
   }

   temp = findShortestDistance(robot_x-1, robot_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
   if (temp != PA2_MAX_PATH) {
      if (temp < distance) {
         distance = temp;
      }
   }

   // if (distance != PA2_MAX_PATH) {
   //    cout << " current distance: "<< distance << " x: "<< robot_x << " y: " << robot_y << endl;
   // }

   return distance;

}


//helper  function
void fixArr(char c[], int index, int distance, bool clear=false) {
   if (index >= MAX_STRING_SIZE) {
      return;
   }

   if (clear) {
      c[index] = '\0';
   } else {
      if (index == distance-1) {
         c[index] = 'T';
      }
      else if (index >= distance) {
         c[index] = '\0';
      }
   }
   fixArr(c, index+1, distance, clear);
}

int findPathSequence(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, 
   int robot_full_energy, char result_sequence[], const char map[MAP_HEIGHT][MAP_WIDTH],
   char temp_map[MAP_HEIGHT][MAP_WIDTH]) {
      
   int true_distance = PA2_MAX_PATH;

   // if target is in B or out of bound
   if (map[target_y][target_x] == 'B' || target_y < 0 || target_y >= MAP_HEIGHT || target_x < 0 || target_y >= MAP_WIDTH) {
      return PA2_MAX_PATH;
   }

   if (map[robot_y][robot_x] == 'B' || robot_y < 0 || robot_x < 0 || robot_y >= MAP_HEIGHT || robot_x >= MAP_WIDTH) {
      return true_distance;
   }

   int d = robot_full_energy - robot_energy;

   if (d == 0) {
      fixArr(result_sequence, 0, MAX_STRING_SIZE, true);
      temp_map[target_y][target_x] = char(robot_full_energy);
      true_distance = findShortestDistance(robot_x, robot_y, target_x, target_y, robot_energy, 
         robot_full_energy, map, temp_map);
      // cout << "true distance: " << true_distance << endl;
      // if un-reachable
      if (true_distance == PA2_MAX_PATH || true_distance == 0) {
         return PA2_MAX_PATH;
      } else if (true_distance == 1) {
         result_sequence[0] = 'T';
         return true_distance;
      }
      result_sequence[MAX_STRING_SIZE-1] = char(true_distance);
   } else {

      // cout << robot_x << " " << robot_y << " " << target_x << " " << target_y << " " << 
      // robot_energy << " " << robot_full_energy << " " << endl;

      int d_2;
      if (temp_map[robot_y][robot_x] == 'V') {
         d_2 = findShortestDistance(robot_x, robot_y, target_x, target_y, temp_map[target_y][target_x], 
            temp_map[target_y][target_x], map, temp_map);
         temp_map[robot_y][robot_x] = 'V';
      } else {
         d_2 = findShortestDistance(robot_x, robot_y, target_x, target_y, temp_map[target_y][target_x], 
            temp_map[target_y][target_x], map, temp_map);
      }

      if (d_2 + d > int(result_sequence[MAX_STRING_SIZE-1])) {
         // cout << "wrong direction: x: " << robot_x << " y: " << robot_y << endl;
         // cout << "\td: " << d << " d_2: " << d_2 << " true_distance: " << int(result_sequence[MAX_STRING_SIZE-1]) << endl;  
         return true_distance;
      }
      else {
         // cout << "correct x: " << robot_x << " y: " << robot_y << endl;
         // cout << "\td: " << d << " d_2: " << d_2 << " true_distance: " << int(result_sequence[MAX_STRING_SIZE-1]) << endl;
      }

   }

   if (robot_x == target_x && robot_y == target_y && d+1 == int(result_sequence[MAX_STRING_SIZE-1])) {
      // cout << "path found and match" << endl;
      result_sequence[MAX_STRING_SIZE-1] = '\0';
      return 0;
   }


   // for debugging
   // cout << "x: " << robot_x << " y: " << robot_y << " energy: " << robot_energy << endl;


   if (map[robot_y][robot_x] == 'C' && temp_map[robot_y][robot_x] != 'V') {
      temp_map[robot_y][robot_x] = 'V';
      findPathSequence(robot_x, robot_y, target_x, target_y, temp_map[target_y][target_x], temp_map[target_y][target_x]+d, result_sequence, map, temp_map);

      temp_map[robot_y][robot_x] = '\0';
      robot_energy++;
      return 0;
   }

   if (robot_energy <= 0) {
      robot_energy++;
      return 0;
   }

   result_sequence[d] = 'U';
   findPathSequence(robot_x, robot_y-1, target_x, target_y, robot_energy-1, robot_full_energy, result_sequence, map, temp_map);
   if (result_sequence[MAX_STRING_SIZE-1] == '\0') {
      if (d == 0) {
         // cout << "first stack" << endl;
         fixArr(result_sequence, 0, true_distance);
         return true_distance;
      }
      else {
         return true_distance;
      }
   }

   result_sequence[d] = 'R';
   findPathSequence(robot_x+1, robot_y, target_x, target_y, robot_energy-1, robot_full_energy, result_sequence, map, temp_map);
   if (result_sequence[MAX_STRING_SIZE-1] == '\0') {
      if (d == 0) {
         // cout << "first stack" << endl;
         fixArr(result_sequence, 0, true_distance);
         return true_distance;
      }
      else {
         return true_distance;
      }
   }

   result_sequence[d] = 'D';
   findPathSequence(robot_x, robot_y+1, target_x, target_y, robot_energy-1, robot_full_energy, result_sequence, map, temp_map);
   if (result_sequence[MAX_STRING_SIZE-1] == '\0') {
      if (d == 0) {
         // cout << "first stack" << endl;
         fixArr(result_sequence, 0, true_distance);
         return true_distance;
      }
      else {
         return true_distance;
      }
   }

   result_sequence[d] = 'L';
   findPathSequence(robot_x-1, robot_y, target_x, target_y, robot_energy-1, robot_full_energy, result_sequence, map, temp_map);
   if (result_sequence[MAX_STRING_SIZE-1] == '\0') {
      if (d == 0) {
         // cout << "first stack" << endl;
         fixArr(result_sequence, 0, true_distance);
         return true_distance;
      }
      else {
         return true_distance;
      }
   }

   return true_distance;
}

int findFarthestPossibleCharger(int robot_x, int robot_y, int robot_original_x, int robot_original_y, 
   int &target_x, int &target_y, int robot_energy, int robot_full_energy,
   const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH]) {

   int distance = -1;

   // for debugging
   // cout << "x: " << robot_x << " y: " << robot_y << " energy: " << robot_energy << endl;

   if (map[robot_y][robot_x] == 'B' || robot_y < 0 || robot_x < 0 || robot_y >= MAP_HEIGHT || robot_x >= MAP_WIDTH) {
      return distance;
   }

   if (map[robot_y][robot_x] == 'C') {
      int d_new = findShortestDistance(robot_original_x, robot_original_y, robot_x, robot_y, robot_full_energy, robot_full_energy, map, temp_map);
      int d_origin = findShortestDistance(robot_original_x, robot_original_y, target_x, target_y, robot_full_energy, robot_full_energy, map, temp_map);
      if (d_origin == PA2_MAX_PATH || d_new > d_origin) {
         target_x = robot_x;
         target_y = robot_y;
         return d_new;
      }
      return d_origin;
   }

   if (robot_energy <= 0) {
      robot_energy++;
      return distance;
   }

   int temp;
   temp = findFarthestPossibleCharger(robot_x, robot_y-1, robot_original_x, robot_original_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
   if (temp != -1) {
      if (temp > distance) {
         // cout << "return distance: "<<temp << " init distance: " << distance << endl;
         // cout << robot_x << " " << robot_y+1 << endl;
         distance = temp; 
      }
   }

   temp = findFarthestPossibleCharger(robot_x+1, robot_y, robot_original_x, robot_original_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
   if (temp != -1) {
      if (temp > distance) {
         // cout << "return distance: "<<temp << " init distance: " << distance << endl;
         // cout << robot_x << " " << robot_y << endl;
         distance = temp; 
      }
   }

   temp = findFarthestPossibleCharger(robot_x, robot_y+1, robot_original_x, robot_original_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
   if (temp != -1) {
      if (temp > distance) {
         // cout << "return distance: "<<temp << " init distance: " << distance << endl;
         // cout << robot_x << " " << robot_y << endl;
         distance = temp; 
      }
   }

   temp = findFarthestPossibleCharger(robot_x-1, robot_y, robot_original_x, robot_original_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
   if (temp != -1) {
      
      if (temp > distance) {
         // cout << "return distance: "<<temp << " init distance: " << distance << endl;
         // cout << robot_x << " " << robot_y << endl;
         distance = temp; 
      }
   }

   // if (distance != PA2_MAX_PATH) {
   //    cout << " current distance: "<< distance << " x: "<< robot_x << " y: " << robot_y << endl;
   // }

   return distance;
}