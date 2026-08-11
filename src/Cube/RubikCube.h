#pragma once

#include "Cube.h"
#include <vector>

enum class Rotation
{
    None,
    Top,
    Bottom,
    Left,
    Right,
    Front,
    Back
};

class RubikCube
{
public:
    RubikCube();

    void RotateTop();
    void RotateBottom();
    void RotateLeft();
    void RotateRight();
    void RotateFront();
    void RotateBack();

    void Update();

    void UpdateRotation();
    void UpdateImGui();

    void Randomize();
    void Reset();

    float GetRotationTime() const;

    void SetRotType(Rotation type);
    void SetRotState(bool state);

    const std::vector<Cubelet>& GetCubelets() const;

private:

    void InitCubeletes();


private:
    std::vector<Cubelet> m_Cubelets;

private:

    float m_Rotate = 5.0f;
    float m_Time = 0.0f;
    bool m_Rotation = false;
    Rotation m_Type = Rotation::None;
};