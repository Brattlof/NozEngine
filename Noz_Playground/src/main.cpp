#include <Noz.hpp>

class HealthComponent : public Noz::BaseComponent
{
private:
	float m_Health;
public:
	void Reset(float health) { this->m_Health = health; }
	float GetHealth() { return this->m_Health; }
};

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
#ifdef NOZ_DEBUG
	NOZ_ALLOCATE_CONSOLE
#endif

	Noz::EntityAdmin admin;

	Noz::Entity& entity = admin.CreateEntity<Noz::Entity>();
	entity.Add<HealthComponent>(100.f);

	NOZ_LOG_INFO(NOZ_OBFUSCATE("Entity->Health: %f"), entity.Get<HealthComponent>()->GetHealth());

	while (true)
	{
		if (GetAsyncKeyState(VK_END) & 0x1) break;
	}

#ifdef NOZ_DEBUG
	NOZ_FREE_CONSOLE
#endif

	return 0;
}