#pragma once
#include "Context.h"

namespace BB
{
	struct AppInterface
	{
		inline virtual ~AppInterface() = default;

	protected:
		inline virtual void OnUpdate() {}
		inline virtual void OnAttach() {}
		inline virtual void OnDetach() {}

	private:
		friend struct Application;
		AppContext* m_Context;
		uint32_t m_LayerID;
	};

	template<typename Layer>
	inline Layer* GetLayer()
	{
		static_assert(std::is_base_of<AppInterface, Layer>::value);

		auto itr = std::find_if(m_Contect->Layers.begin(), m_Context->Layers.end(), [this](auto Layer)
		{
				return (Layer->m_LayerID == TypeID<Layer>());
		});

		if (itr != m_Context->Layers.end())
		{
			return static_cast<Layer*>(*itr);
		}

		return nullptr;
	}

	template<typename Layer, typename... Args>
	inline Layer* AttachLayer(Args&&... args)
	{
		static_assert(std::is_base_of<AppInterface, Layer>::value);

		if (GetLayer<Layer>() != nullptr)
		{
			BB_ERROR("Layer allready attached");
			return nullptr;
		}

		auto layer = new Layer(std::forward<Args>(args)...);
		m_Context->Layers.push_back(layer);
		layer->m_LayerID() = TypeID<Layer>();
		layer->m_Context = m_Context;

		layer->OnAttach();

		return layer;
	}
}
