#pragma once
#include "Singleton.hpp"
#include "GenericTable.hpp"

struct ProcessPath
{
	WCHAR Path[MAX_PATH]{ 0 };
};


struct _CompareProcessPath
{
	RTL_GENERIC_COMPARE_RESULTS
		operator()(PVOID First, PVOID Second)
	{
		auto firstData = reinterpret_cast<ProcessPath*>(First);
		auto secondData = reinterpret_cast<ProcessPath*>(Second);
		RTL_GENERIC_COMPARE_RESULTS result = GenericEqual;

		if (_wcsicmp(firstData->Path, secondData->Path) == 0)
		{
			result = GenericEqual;
		}
		else if (_wcsicmp(firstData->Path, secondData->Path) > 0)
		{
			result = GenericGreaterThan;
		}
		else if (_wcsicmp(firstData->Path, secondData->Path) < 0)
		{
			result = GenericLessThan;
		}

		return result;
	}
};

class CRules : public Singleton<CRules>
{
public:
	NTSTATUS Initialized();
	VOID     Finalized();

	NTSTATUS AddTrustProcess(IN CONST PWCHAR ProcessName);
	NTSTATUS DelTrustProcess(IN CONST PWCHAR ProcessName);
	BOOLEAN  FindTrustProcess(IN CONST PWCHAR ProcessName);

	NTSTATUS AddProtectProcess(IN CONST PWCHAR ProcessName);
	NTSTATUS DelProtectProcess(IN CONST PWCHAR ProcessName);
	BOOLEAN  FindProtectProcess(IN CONST PWCHAR ProcessName);

public:
	GenericTable<ProcessPath, _CompareProcessPath>* m_tableOfTrustProcess;
	GenericTable<ProcessPath, _CompareProcessPath>* m_tableOfProtectProcess;
};

#define CRULES_INSTANCE()				(CRules::getInstance())
#define CRULES_INIT()					(CRules::getInstance()->Initialized())
#define CRULES_DESTROY()				(CRules::getInstance()->Finalized())

#define CRULES_ADD_TRUST_PROCESS(X)		(CRules::getInstance()->AddTrustProcess(X))
#define CRULES_DEL_TRUST_PROCESS(X)		(CRules::getInstance()->DelTrustProcess(X))
#define CRULES_FIND_TRUST_PROCESS(X)	(CRules::getInstance()->FindTrustProcess(X))

#define CRULES_ADD_PROTECT_PROCESS(X)	(CRules::getInstance()->AddProtectProcess(X))
#define CRULES_DEL_PROTECT_PROCESS(X)	(CRules::getInstance()->DelProtectProcess(X))
#define CRULES_FIND_PROTECT_PROCESS(X)	(CRules::getInstance()->FindProtectProcess(X))
