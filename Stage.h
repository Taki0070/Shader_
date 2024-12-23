#pragma once
#include "Engine/GameObject.h"

enum State
{
    S3D,
    SPO,
};


struct CONSTBUFFER_STAGE
{
    XMFLOAT4 lightPosition; //�����ʒu
    XMFLOAT4 eyePosition;//���_�̈ʒu
};


class Stage : public GameObject
{
    int hModel_;    
    int hBunny_;

    float hMaru_[4];

    ID3D11Buffer* pConstantBuffer_;
    void InitConstantBuffer();

public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};