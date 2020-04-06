#pragma once

#include "stdafx.h"

struct vec2i {
    int x, y;
};

inline bool operator==(vec2i a, vec2i b) {
    return a.x==b.x && a.y==b.y;
}

inline bool operator!=(vec2i a, vec2i b) {
    return !(a == b);
}

typedef std::vector<std::vector<bool>> TileMap;

class MathsUtils {
public:
	static void printMatrix(mat4 matrix) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				printf("%f,", matrix[x][y]);
			}
			printf("\n");
		}
	}

	static void printMatrix(mat3 matrix) {
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				printf("%f,", matrix[x][y]);
			}
			printf("\n");
		}
	}

	static void matrixToEulerAngles(mat4 matrix) {

	}

	static float squareDistance(vec3 a, vec3 b) {
		return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
	}

	static float dotProduct(vec3 a, vec3 b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

        inline float distance(vec2i a, vec2i b) {
            return std::sqrt(a.x*a.x + b.x*b.x);
        }

        static std::vector<vec2i> findPath(TileMap map, vec2i start, vec2i target) {
            struct QueueElement {
                float heuristic;
                float traveled;
                vec2i position;
            };

            class QueueCompare {
                public:
                    bool operator()(QueueElement a, QueueElement b) {
                        return (a.heuristic + a.traveled) > (b.heuristic + b.traveled);
                    }
            };

            std::priority_queue<QueueElement, std::vector<QueueElement>, QueueCompare> q;
            int mapWidth = map.size(); // in memory layout this is height!
            int mapHeight = map[0].size(); // in memory layout this is width!

            std::vector<std::vector<QueueElement>> from(mapWidth);
            for (auto& column : from) {
                column.resize(mapHeight);
            }

            QueueElement startElement = {distance(start, target), 0.0f, start};
            q.push(startElement);

            while (!q.empty()) {
                auto el = q.top();
                q.pop();

                if (el.position == target) {
                    // reconstruct path
                    std::vector<vec2i> result;
                    result.push_back(el.position);
                    vec2i previous = from[el.position.x][el.position.y].position;
                    while (previous != start) {
                        result.push_back(previous);
                        previous = from[previous.x][previous.y].position;
                    }
                    return result;
                }

                int dx[] = {1, 0, -1, 0};
                int dy[] = {0, 1, 0, -1};
                for (int i = 0; i < 4; i++) {
                    vec2i newPosition = {el.position.x+dx[i], el.position.y+dy[i]};
                    if (newPosition.x >= mapWidth  || newPosition.x < 0 ||
                            newPosition.y >= mapHeight || newPosition.y < 0 ||
                            map[newPosition.x][newPosition.y])
                        continue;
                    QueueElement newElement;
                    newElement.heuristic = distance(newPosition, target);
                    newElement.traveled = el.traveled + 1.0f;
                    newElement.position = newPosition;
                    auto& f = from[newPosition.x][newPosition.y];
                    if (f.traveled < 0.1f || newElement.traveled < f.traveled) {
                        f.traveled = newElement.traveled;
                        f.position = el.position;
                        q.push(newElement);
                    }
                }
            }

            // there is no path from start to target
            return {};
        }
};
