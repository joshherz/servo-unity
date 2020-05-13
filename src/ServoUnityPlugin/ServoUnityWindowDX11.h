﻿//
// ServoUnityWindowDX11.h
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at https ://mozilla.org/MPL/2.0/.
//
// Copyright (c) 2019-2020 Mozilla, Inc.
//
// Author(s): Philip Lamb
//

#pragma once
#include "ServoUnityWindow.h"
#ifdef SUPPORT_D3D11
#include <cstdint>
#include <string>
#include <Windows.h>
#include "IUnityInterface.h"

struct ID3D11Texture2D;

class ServoUnityWindowDX11 : public ServoUnityWindow
{
private:

	ID3D11Texture2D* m_servoTexPtr;
	void* m_servoTexHandle;
	Size m_size;
	int m_format;
	void *m_unityTexPtr;

public:
	static void initDevice(IUnityInterfaces* unityInterfaces);
	static void finalizeDevice();

	ServoUnityWindowDX11(int uid, int uidExt, Size size);
	~ServoUnityWindowDX11() ;
    //ServoUnityWindowDX11(const ServoUnityWindowDX11&) = delete;
	//void operator=(const ServoUnityWindowDX11&) = delete;

	bool init(PFN_WINDOWCREATEDCALLBACK windowCreatedCallback) override;
    RendererAPI rendererAPI() override {return RendererAPI::DirectX11;}
	Size size() override;
	void setSize(Size size) override;
	void setNativePtr(void* texPtr) override;
	void* nativePtr() override;

	// Must be called from render thread.
	void requestUpdate(float timeDelta) override;

	int format() override { return m_format; }

    void CloseServoWindow() override {}
	void pointerEnter() override;
	void pointerExit() override;
	void pointerOver(int x, int y) override;
	void pointerPress(int x, int y) override;
	void pointerRelease(int x, int y) override;
	void pointerScrollDiscrete(int x, int y) override;
	void keyPress(int charCode) override;
};

#endif // SUPPORT_D3D11