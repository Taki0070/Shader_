#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"



void Stage::InitConstantBuffer()
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CONSTBUFFER_STAGE);
    cb.Usage = D3D11_USAGE_DYNAMIC;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;
    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
    }
}

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), pConstantBuffer_(nullptr)
{
    hModel_ = -1;
    hBunny_ = -1;

    hMaru_[1] = -1;
    hMaru_[2] = -1;
    hMaru_[3] = -1;
    hMaru_[4] = -1;
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    hModel_ = Model::Load("Assets\\Ball.fbx");
    hBunny_ = Model::Load("Assets\\maru.fbx");

    hMaru_[1] = Model::Load("Assets\\maru.fbx");
    hMaru_[2] = Model::Load("Assets\\maru2.fbx");
    hMaru_[3] = Model::Load("Assets\\maru3.fbx");
    hMaru_[4] = Model::Load("Assets\\maru3.fbx");

    Camera::SetPosition(XMFLOAT3{ 9, 0.4, -5.8 });
    Camera::SetTarget(XMFLOAT3{ 0,0.8,0 });

    InitConstantBuffer();
}

//�X�V
void Stage::Update()
{
    transform_.rotate_.y += 1.5f;
  
    if (Input::IsKey(DIK_A))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x - 0.1f,p.y, p.z,p.w };
        Direct3D::SetLightPos(p);
    }
    if (Input::IsKey(DIK_D))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x + 0.1f,p.y, p.z,p.w };
        Direct3D::SetLightPos(p);
    }
    if (Input::IsKey(DIK_W))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x,p.y, p.z + 0.1f,p.w };
        Direct3D::SetLightPos(p);
    }
    if (Input::IsKey(DIK_S))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x ,p.y, p.z - 0.1f,p.w };
        Direct3D::SetLightPos(p);
    }
    if (Input::IsKey(DIK_UP))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x,p.y + 0.01f, p.z,p.w };
        Direct3D::SetLightPos(p);
    }
    if (Input::IsKey(DIK_DOWN))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x ,p.y - 0.01f, p.z,p.w };
        Direct3D::SetLightPos(p);
    }

 
    CONSTBUFFER_STAGE cb;
    cb.lightPosition = Direct3D::GetLightPos();
    XMStoreFloat4(&cb.eyePosition, Camera::GetPosition());
    
    D3D11_MAPPED_SUBRESOURCE pdata;
    Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃A�N�Z�X���~�߂�
    memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�
    Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ

    //�R���X�^���g�o�b�t�@
    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p


}

//�`��
void Stage::Draw()
{

    Transform ltr;
    ltr.position_ = { Direct3D::GetLightPos().x,Direct3D::GetLightPos().y,Direct3D::GetLightPos().z };
    ltr.scale_ = { 0.1,0.1,0.1 };
    Model::SetTransform(hModel_, ltr);
    Model::Draw(hModel_);


   static Transform tr;
   tr.rotate_.y += 1.0f;

    for (int i = 1; i <= 3; i++) {
        tr.scale_ = { 0.25f, 0.25f, 0.25f };
        tr.position_ = { 1.0f * i, 0.5f, 0.0f };

        Model::SetTransform(hMaru_[i], tr);
        Model::Draw(hMaru_[i]);  
    }

    
}

//�J��
void Stage::Release()
{
}