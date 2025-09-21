#pragma once
#include "Core/Application.hpp"

namespace SMB
{
	class AppSMB : public Core::Application
	{
	public:
		AppSMB() noexcept;
		virtual ~AppSMB() noexcept override = default;

		virtual void OnEvent(const std::optional<sf::Event>& event) override;
	};
}
