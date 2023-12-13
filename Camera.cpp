#include "Camera.h"

Camera::Camera(const Cartesian3& position, const Cartesian3& direction, const Cartesian3& up)
{
    m_cameraPositon = position;
    m_cameraDirection = direction;
    m_yaw = 0.0f;
    
    m_cameraSpeed = 10.0f;
    auto forward = Cartesian3(0, 0, -1);

    forward.Rotate(m_yaw, up);
    forward = forward.unit();

    Cartesian3 x = up;
    x = x.cross(forward);
    x = x.unit();

    Cartesian3 u = forward.cross(x);
    u = u.unit();

    m_cameraDirection = forward;

    m_viewMatrix = Matrix4::ViewMatrix(m_cameraPositon, m_cameraPositon + m_cameraDirection, up);
}
