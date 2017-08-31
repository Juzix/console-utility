#include "base.h"
bool Byte2Hexstr(const BYTE* pbyteSource, DWORD dwSize, char* pcharDest, bool bHas0xHeader)
{
	if (pbyteSource==NULL || pcharDest==NULL)
	{
		return false;
	}

	int nIndex = 0;
	if (bHas0xHeader)
	{
		memcpy(pcharDest, "0x", 2);
		nIndex = 2;
	}
	for(int i=0; i<dwSize; i++)  
	{  
		int high = pbyteSource[i]/16, low = pbyteSource[i]%16;

		pcharDest[nIndex] = (high<10) ? ('0' + high) : ('A' + high - 10);  
		pcharDest[nIndex+1] = (low<10) ? ('0' + low) : ('A' + low - 10);  
		nIndex += 2;  
	}
	pcharDest[nIndex] = '\0';

	return true;
}

bool Hexstr2Byte( const BYTE* pbSource,  const DWORD dwSize,  BYTE* pbDest)
{
	if (pbSource==NULL || pbDest==NULL)
	{
		return false;
	}

	int nIndex = 0;
	for(int i=0; i<dwSize; i++)
	{
		BYTE bhigh = (pbSource[nIndex]>='a' && pbSource[nIndex]<='z')? ('A'+pbSource[nIndex]-'a'):(pbSource[nIndex]);
		BYTE blow = (pbSource[nIndex+1]>='a' && pbSource[nIndex+1]<='z')? ('A'+pbSource[nIndex+1]-'a'):(pbSource[nIndex+1]);
		int nhigh = 0, nlow = 0;
		nhigh = (bhigh>='0' && bhigh<='9')? (bhigh-'0'):(bhigh-'A'+10);
		nlow = (blow>='0' && blow<='9')? (blow-'0'):(blow-'A'+10);
		pbDest[i] = nhigh*16 + nlow;
		nIndex += 2;
	}

	return true;
}

bool LittleEndian()
{
	union
	{
		int i;
		char c;
	}udata;
	udata.i = 1;
	return (udata.c == 1);
}

void CopyIntFromMemory( const BYTE* pbnMemory,  DWORD dwSize,  DWORD* pdwOut)
{
	//自适应大小端拷贝内存到整数
	if (LittleEndian())
	{
		char* pcOut = (char*)pdwOut;
		while(dwSize--){

			BYTE b = *(pbnMemory+dwSize);
			*pcOut++ = *(pbnMemory+dwSize);
		}
	}
	else{
		memcpy(pdwOut+sizeof(DWORD)-dwSize, pbnMemory, dwSize);
	}
}

void CopyMemoryFromInt( BYTE* pbDest,  DWORD dwValue,  DWORD dwValueSize)
{
	//自适应大小端拷贝整数到内存
	if (LittleEndian())
	{
		char* pcValue = (char*)&dwValue;
		while(dwValueSize--)
			*(pbDest+dwValueSize) = *pcValue++;
	}
	else{
		memset(pbDest, dwValue, dwValueSize);
	}
}

int CalcNumByte( const long long llNum)
{
	if (llNum>0xffffffffffffff)
	{
		return -1;//超出计算返回
	}
	long long llTemp = 0;
	int i = 1;
	while(llTemp=llNum>>(i*8))
		i++;

	return i;
}

bool web3RlpRemoveVRS( const BYTE* pbSource,  BYTE* pbDst,  DWORD* pdwDstLen)
{	
	//去除web3自动补充的vrs3个字节
	if (pbSource==NULL || pbDst==NULL){
		return false;
	}

	DWORD dwLen = 0;
	DWORD dwLenByte = *pbSource-0xf7;
	DWORD dwNewLenByte = 0;

	CopyIntFromMemory(pbSource+1, dwLenByte, &dwLen);
	dwNewLenByte = CalcNumByte(dwLen-3);
	memset(pbDst, 0xf7+dwNewLenByte, 1);
	CopyMemoryFromInt(pbDst+1, dwLen-3, dwNewLenByte);
	
	memcpy(pbDst+1+dwNewLenByte, pbSource+1+dwLenByte, dwLen-3);
	*pdwDstLen = dwLen-3+1+dwNewLenByte;

	return true;
}

bool rlpRemoveNonce( const BYTE* pbSource,  const DWORD dwNonce,  BYTE* pbDst,  DWORD* pdwDstLen)
{
	if (pbSource == NULL || pbDst == NULL){
		return false;
	}

	DWORD dwLen = 0;
	DWORD dwLenByte = *pbSource - 0xf7;
	DWORD dwNewLenByte = 0;
	DWORD dwNonceByte = CalcNumByte(dwNonce);
	DWORD dwNonceRlpByte = (dwNonceByte>1)? dwNonceByte+1:dwNonceByte;

	CopyIntFromMemory(pbSource+1, dwLenByte, &dwLen);
	dwNewLenByte = CalcNumByte(dwLen-dwNonceRlpByte);
	memset(pbDst, 0xf7+dwNewLenByte, 1);
	CopyMemoryFromInt(pbDst+1, dwLen-dwNonceRlpByte, dwNewLenByte);
	memcpy(pbDst+1+dwNewLenByte, pbSource+1+dwLenByte+dwNonceRlpByte, dwLen-dwNonceRlpByte);
	*pdwDstLen = dwLen-dwNonceRlpByte+1+dwNewLenByte;//原长度-Nonce所占rlp长度+0xf7+新长度所占字节

	return true;
}