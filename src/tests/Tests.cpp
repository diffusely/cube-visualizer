#include "Tests.h"
#include "imgui/imgui.h"

namespace test {

	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{}

	void TestMenu::OnImGuiRender()
	{
		for (auto& [first, second] : m_Tests) {
			if (ImGui::Button(first.c_str()))
				m_CurrentTest = second();
		}
	}
}

