#pragma once
#include "BaseScene.h"

namespace SceneManager {

	/// <summary>
	/// SceneManagerを初期化する関数。
	/// </summary>
	int InitManager();

	/// <summary>
	/// SceneManagerのメモリを開放する関数。
	/// </summary>
	void ReleaseManager();

	/// <summary>
	/// シーンを変更する関数。
	/// </summary>
	/// <param name="name">変更したいシーン名</param>
	/// <returns>成功した場合は0を返します。失敗は-1。</returns>
	int ChangeScene(std::string name);

	/// <summary>
	/// 現在のシーンを取得する関数。
	/// </summary>
	/// <returns>ポインタとして返します（現在のシーンが無い場合はnullptr）。</returns>
	BaseScene* GetCurrentScene();

	/// <summary>
	/// シーン名から、シーンを取得する関数。
	/// </summary>
	/// <param name="name">シーン名</param>
	/// <returns>ポインタとして返します（シーンが見つからない場合はnullptr）。</returns>
	BaseScene* GetScene(std::string name);
}