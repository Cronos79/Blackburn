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

	public:
		template<typename Layer>
		inline Layer* GetLayer()
		{
			static_assert(std::is_base_of<AppInterface, Layer>::value);

			auto itr = std::find_if(m_Context->Layers.begin(), m_Context->Layers.end(), [this](auto layer)
				{
					return (layer->m_LayerID == TypeID<Layer>());
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
			layer->m_LayerID = TypeID<Layer>();
			layer->m_Context = m_Context;

			layer->OnAttach();

			return layer;
		}

		template<typename Layer>
		inline void DetachLayer()
		{
			static_assert(std::is_base_of<AppInterface, Layer>::value);

			m_Context->Dispatcher.PostTask([this]
				{
					m_Context->Layers.erase(std::remove_if(m_Context->Layers.begin(),
						m_Context->Layers.end(), [this](auto& layer)
						{
							if (layer->m_LayerID == TypeID<Layer>())
							{
								m_Context->Dispatcher.EraseListener(layer->m_LayerID);
								BB_DELETE(layer);
								return true;
							}
							return false;
						}),
						m_Context->Layers.end());
				});
		}

		template<typename Event, typename Callback>
		inline void AttachCallback(Callback&& callback)
		{
			m_Context->Dispatcher.AttachCallback<Event>(std::move(callback), m_LayerID);
		}

		template<typename Event, typename... Args>
		inline void PostEvent(Args&&... args)
		{
			m_Context->Dispatcher.PostEvent<Event>(std::forward<Args>(args)...);
		}

		template<typename Task>
		inline void PostTask(Task&& task)
		{
			m_Context->Dispatcher.PostTask(std::move(task));
		}

		template<typename Event>
		inline void DetachCallback()
		{
			m_Context->Dispatcher.DetachCallback<Event>(m_LayerID);
		}
	};	
}
