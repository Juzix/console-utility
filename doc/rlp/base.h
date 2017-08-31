#ifndef __BASE_H__
#define __BASE_H__
#include <windows.h>
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef int                 INT;
typedef unsigned int        UINT;
typedef signed int LONG32, *PLONG32;

bool Byte2Hexstr(const BYTE* pbyteSource, DWORD dwSize, char* pcharDest, bool bHas0xHeader=false);
//
bool Hexstr2Byte( const BYTE* pbSource,  const DWORD dwSize,  BYTE* pbDest);
//
bool LittleEndian();
//
int CalcNumByte( const long long llNum);
//
void CopyIntFromMemory( const BYTE* pbnMemory,  DWORD dwSize,  DWORD* pdwOut);
//
void CopyMemoryFromInt( BYTE* pbDest,  DWORD dwValue,  DWORD dwValueSize);
//
bool web3RlpRemoveVRS( const BYTE* pbSource,  BYTE* pbDst,  DWORD* pdwDstLen);
//
bool rlpRemoveNonce( const BYTE* pbSource,  const DWORD dwNonce,  BYTE* pbDst,  DWORD* pdwDstLen);


#endif