#pragma once

#include<iostream>
#include<fstream>
#include<cstdio>
#include<vector>
#include<thread>
#include<mutex>
#include<string>
#include<cstring>
#include<cstdio>
#include<map>
#include<unordered_map>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<utility>


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/constants.hpp>
#include<stb_image.h>

#include<windows.h> //ALERT

using std::cout;
using std::vector;
using std::map;
using std::unordered_map;
using std::pair;
using std::string;
using std::to_string;
using std::ifstream;
using std::getline;
using std::mutex;
using std::thread;
using std::max;
using std::min;

#define hashmap std::unordered_map;

using glm::mat3;
using glm::mat4;
using glm::vec2;
using glm::vec3;
using glm::vec4;

#define uint unsigned int

#include "Log.h"
#include "Colors.h"
#include "Directions.h"
#include "Constants.h"