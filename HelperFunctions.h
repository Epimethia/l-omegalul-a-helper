#pragma once


struct ID3D11Device;
struct ID3D11ShaderResourceView;
struct ImVec2; 

void SetP3DDevice(ID3D11Device* _P3DDevice);
bool LoadTextureFromFile(const char* _FilePath, ID3D11ShaderResourceView** out_srv);