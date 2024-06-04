//=============================================
//
//3DTemplate[objectX.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "objectX.h"
#include "renderer.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CObjectX::CObjectX(int nPriority):CObject(nPriority)
{
	m_pBuffMat = nullptr;
	m_pMesh = nullptr;
	m_pTexture = nullptr;
}

//=============================================
//�f�X�g���N�^
//=============================================
CObjectX::~CObjectX()
{
}

//=============================================
//������
//=============================================
HRESULT CObjectX::Init()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	if (m_pBuffMat == nullptr && m_pMesh == nullptr)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\face.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}


	D3DXMATERIAL* pMat; //�}�e���A���|�C���^
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	int nNumVtx; //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff; //���_�o�b�t�@�̃|�C���^

		//���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���f���̏����ʒu
	m_minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //���f���̍ŏ��ʒu
	m_maxpos = D3DXVECTOR3(-10000.0f, -1000000.0f, -100000.0f); //���f���̍ő�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̕���

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//x���W�̍ő�l�ŏ��l�`�F�b�N
		if (vtx.x > m_maxpos.x)
		{
			m_maxpos.x = vtx.x;
		}
		if (vtx.x < m_minpos.x)
		{
			m_minpos.x = vtx.x;
		}

		//y���W�̍ő�l�ŏ��l�`�F�b�N
		if (vtx.y > m_maxpos.y)
		{
			m_maxpos.y = vtx.y;
		}
		if (vtx.y < m_minpos.y)
		{
			m_minpos.y = vtx.y;
		}

		//z���W�̍ő�l�ŏ��l�`�F�b�N
		if (vtx.z > m_maxpos.z)
		{
			m_maxpos.z = vtx.z;
		}
		if (vtx.z < m_minpos.z)
		{
			m_minpos.z = vtx.z;
		}
	}

	m_pMesh->UnlockVertexBuffer();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CObjectX::Uninit()
{
	//���b�V���̔j��
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
}

//=============================================
//�X�V
//=============================================
void CObjectX::Update()
{
}

//=============================================
//�`��
//=============================================
void CObjectX::Draw()
{
	//�f�o�C�X�̎擾
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ�
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

//�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y,m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	D3DXMATERIAL* pMat; //�}�e���A��

	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		////�e�N�X�`���̐ݒ�
		//pDevice->SetTexture(0, g_apTextureModel[m_nType][nCntMat]);

		//�p�[�c�̐ݒ�
		m_pMesh->DrawSubset(nCntMat);
	}
	//���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���݂��擾
	pDevice->GetMaterial(&matDef);

	//�ۑ����Ă��}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================
//����
//=============================================
CObjectX* CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObjectX* pObjectX = new CObjectX;
	if (pObjectX != nullptr)
	{
		pObjectX->m_pos = pos;
		pObjectX->m_rot = rot;
		pObjectX->Init();
	}
	return pObjectX;
}

//=============================================
//�e�N�X�`���ݒ�
//=============================================
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//=============================================
//���f���ݒ�
//=============================================
void CObjectX::BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh)
{
	m_pBuffMat = pBuffMat;
	m_dwNumMat = dwNumMat;
	m_pMesh = pMesh;
}

D3DXVECTOR3& CObjectX::GetPos()
{
	return m_pos;
}

D3DXVECTOR3& CObjectX::GetRot()
{
	return m_rot;
}

D3DXVECTOR3& CObjectX::GetMinPos()
{
	return m_minpos;
}

D3DXVECTOR3& CObjectX::GetMaxPos()
{
	return m_maxpos;
}

LPD3DXMESH& CObjectX::GetpMesh()
{
	return m_pMesh;
}

LPD3DXBUFFER& CObjectX::GetpBuffMat()
{
	return m_pBuffMat;
}

DWORD& CObjectX::GetNumMat()
{
	return m_dwNumMat;
}
