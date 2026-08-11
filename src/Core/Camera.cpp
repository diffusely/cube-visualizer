#include "Camera.h"

namespace Camera {
    glm::vec3 cameraPos = glm::vec3(
        -0.347205f,
        4.42031f,
        0
    );

    glm::vec3 cameraUp = glm::vec3(
        0.0f,
        1.0f,
        0.0f
    );



    glm::vec3 GetCameraPosition()
    {
        float yaw = glm::radians(callback::yaw);
        float pitch = glm::radians(callback::pitch);

        float distance = callback::cameraDistance;

        glm::vec3 position;

        position.x = distance * cos(pitch) * sin(yaw);
        position.y = distance * sin(pitch);
        position.z = distance * cos(pitch) * cos(yaw);

        return position;
    }
}