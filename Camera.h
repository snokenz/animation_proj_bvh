#include "Matrix4.h"

class Camera
{
public:
    Camera(const Cartesian3& position, const Cartesian3& direction, const Cartesian3& up);

    Matrix4 GetViewMatrix() const { return m_viewMatrix; } 

    Cartesian3 GetPosition() const { return m_cameraPositon; }
    Cartesian3 GetDirection() const { return m_cameraDirection; }

    void Update()
    {   
        auto up = Cartesian3(0, 1.0f, 0.0f);
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

    void Forward()
    {
        m_cameraPositon = m_cameraPositon + m_cameraSpeed * m_cameraDirection;
    }

    void Back()
    {
        m_cameraPositon = m_cameraPositon - m_cameraSpeed * m_cameraDirection;
    }

    void Up()
    {
        m_cameraPositon.y += m_cameraSpeed;
    }

    void Down()
    {
        m_cameraPositon.y -= m_cameraSpeed; 
    }

    void Right()
    {
        auto right = m_cameraDirection.cross(Cartesian3(0, 1.0f, 0.0f));
        right = right.unit();

        m_cameraPositon = m_cameraPositon + right * m_cameraSpeed;
    }

    void Left()
    {
        auto right = m_cameraDirection.cross(Cartesian3(0, 1.0f, 0.0f));
        right = right.unit();
        m_cameraPositon = m_cameraPositon - right * m_cameraSpeed;
    }

    // QE for yaw right and left 
    void YawRight()
    {
        m_yaw -= m_cameraSpeed;
    }

    void YawLeft()
    {
        m_yaw += m_cameraSpeed;
    }

private:
    float m_cameraSpeed;
    float m_yaw = 0.0f;
    Cartesian3 m_cameraPositon;
    Cartesian3 m_cameraDirection;
    Matrix4 m_viewMatrix;
};