#include "WinFireWall.h"
CWinFireWall::CWinFireWall()
{
	m_p_firewall = NULL;
}

CWinFireWall::~CWinFireWall()
{
	UninitializeFireWall();
}

FW_ERROR_CODE CWinFireWall::InitializeFireWall()
{
	FW_ERROR_CODE ret = FW_NOERROR;
	//firewallʵ��
	INetFwMgr *fwmgr = NULL;		
	//firewall����
	INetFwPolicy *fwpolicy = NULL;
	try
	{
		if (m_p_firewall)
		{
			throw FW_ERR_INITIALIZED;
		}
		
		//�������
		HRESULT hr = CoCreateInstance(__uuidof(NetFwMgr), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwMgr), (PVOID *)&fwmgr);
		if (FAILED(hr))
		{
			throw FW_ERR_CREATE_SETTING_MANAGER;
		}

		//��ȡfirewall����
		hr = fwmgr->get_LocalPolicy(&fwpolicy);
		if (FAILED(hr))
		{
			throw FW_ERR_LOCAL_POLICY;
		}

		hr = fwpolicy->get_CurrentProfile(&m_p_firewall);
		if(FAILED(hr))
		{
			throw FW_ERR_PROFILE;
		}
	}
	catch (FW_ERROR_CODE err)
	{
		ret = err;
	}

	if(fwpolicy)
	{
		fwpolicy->Release();
	}
	if (fwmgr)
	{
		fwmgr->Release();
	}
	return ret;
}

FW_ERROR_CODE CWinFireWall::AddApplication( IN const TCHAR *process_image_file_name, IN const TCHAR *service_name )
{
	FW_ERROR_CODE ret = FW_NOERROR;
	INetFwAuthorizedApplications *p_fw_apps = NULL;
	INetFwAuthorizedApplication *p_fw_app = NULL;
	BSTR bstr_process_image_file_name = NULL;
	BSTR bstr_service_name = NULL;
	HRESULT hr;
	BOOL b_enabled;

	try
	{
		if (service_name == NULL || process_image_file_name == NULL)
		{
			throw FW_ERR_INVALID_ARG;
		}

		if (m_p_firewall == NULL)
		{
			throw FW_ERR_INITIALIZED;
		}
		
		if((ret = this->IsAppEnabled(process_image_file_name, b_enabled)) != FW_NOERROR)
			throw ret;
	
		//������δ��Ȩ
		if (b_enabled == FALSE)
		{
			//��ȡ��Ȩ�������
			hr = m_p_firewall->get_AuthorizedApplications(&p_fw_apps);
			if (FAILED(hr))
			{
				throw FW_ERR_AUTH_APPLICATIONS;
			}
			//�������
			HRESULT hr = CoCreateInstance(__uuidof(NetFwAuthorizedApplication), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwAuthorizedApplication), (PVOID *)&p_fw_app);
			if (FAILED(hr))
			{
				throw FW_ERR_CREATE_SETTING_MANAGER;
			}

			//��ʼ���ַ���
			bstr_process_image_file_name = SysAllocString(process_image_file_name);
			bstr_service_name = SysAllocString(service_name);
			if (SysStringLen(bstr_process_image_file_name) == 0 || SysStringLen(bstr_service_name) == 0)
			{
				throw FW_ERR_CREATE_SETTING_MANAGER;
			}
			//����ʵ��
			hr = p_fw_app->put_ProcessImageFileName(bstr_process_image_file_name);
			if (FAILED(hr))
			{
				throw FW_ERR_PUT_PROCESS_IMAGE_NAME;
			}

			hr = p_fw_app->put_Name(bstr_service_name);
			if (FAILED(hr))
			{
				throw FW_ERR_PUT_REGISTER_NAME;
			}

			//���ʵ��
			hr = p_fw_apps->Add(p_fw_app);
			if (FAILED(hr))
			{
				throw FW_ERR_ADD_TO_COLLECTION;
			}
		}
	}
	catch(FW_ERROR_CODE err)
	{
		ret = err;
	}
	if(bstr_service_name != NULL)
		SysFreeString(bstr_service_name);
	if(bstr_process_image_file_name != NULL)
		SysFreeString(bstr_process_image_file_name);

	if (p_fw_app)
	{
		p_fw_app->Release();
	}
	if (p_fw_apps)
	{
		p_fw_apps->Release();
	}

	return ret;
}

FW_ERROR_CODE CWinFireWall::IsAppEnabled( IN const TCHAR *process_image_file_name, OUT BOOL &enabled )
{
	FW_ERROR_CODE ret = FW_NOERROR;

	HRESULT hr;
	//��Ȩ���ʵ��
	INetFwAuthorizedApplication *pfwapp = NULL;
	//��Ȩ���ʵ������
	INetFwAuthorizedApplications *pfwapps = NULL;
	BSTR bstr_process_image_file_name = NULL;
	VARIANT_BOOL bfwenabled;

	//��ʼ��Ϊδ��Ȩ
	enabled = FALSE;

	try
	{

		if (process_image_file_name == NULL)
		{
			throw FW_ERR_INVALID_ARG;
		}

		if (m_p_firewall == NULL)
		{
			throw FW_ERR_INITIALIZED;
		}

		//��ȡ����Ȩ����
		hr = m_p_firewall->get_AuthorizedApplications(&pfwapps);
		if (FAILED(hr))
		{
			throw FW_ERR_AUTH_APPLICATIONS;
		}
		
		//��ʼ���ַ���
		bstr_process_image_file_name = SysAllocString(process_image_file_name);
		if (SysStringLen(bstr_process_image_file_name) == 0)
		{
			throw FW_ERR_SYS_ALLOC_STRING;
		}

		//ָ������Ŀ���״̬
		hr = pfwapps->Item(bstr_process_image_file_name, &pfwapp);
		if (SUCCEEDED(hr))
		{
			hr = pfwapp->get_Enabled(&bfwenabled);
			if (FAILED(hr))
			{
				throw FW_ERR_APP_ENABLED;
			}

			if(bfwenabled == VARIANT_TRUE)
				enabled = TRUE;
		}

	}
	catch(FW_ERROR_CODE err)
	{
		ret = err;
	}
	if(bstr_process_image_file_name != NULL)
		SysFreeString(bstr_process_image_file_name);
	
	if (pfwapp)
	{
		pfwapp->Release();
	}
	if (pfwapps)
	{
		pfwapps->Release();
	}

	return ret;
}

FW_ERROR_CODE CWinFireWall::UninitializeFireWall()
{
	if (m_p_firewall)
	{
		m_p_firewall->Release();
		m_p_firewall == NULL;
	}

	return FW_NOERROR;
}

