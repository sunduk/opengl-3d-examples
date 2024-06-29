#include <functional>
#include <map>
#include <stdlib.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Examples_Main.h"
#include "Example01.h"
#include "Example02.h"
#include "Example03.h"
#include "Example04.h"
#include "Example05.h"
#include "Example06.h"
#include "Example07.h"
#include "Example08.h"
#include "Example09.h"
#include "Example10.h"
#include "Example11.h"
#include "Example12.h"
#include "Example13.h"

void PrintMenu()
{
	std::cout << "==========================" << std::endl;
	std::cout << " 0. Clear" << std::endl;
	std::cout << " 1. Window -----------------[Example01.cpp]" << std::endl;
	std::cout << " 2. Triangle, Rectangle ----[Example02.cpp]" << std::endl;
	std::cout << " 3. Color ------------------[Example03.cpp]" << std::endl;
	std::cout << " 4. Texture wrap:fit -------[Example04.cpp]" << std::endl;
	std::cout << " 5. Texture wrap:repeat" << std::endl;
	std::cout << " 6. Texture wrap:clamp to edge" << std::endl;
	std::cout << " 7. Texture wrap:mirrored repeat" << std::endl;
	std::cout << " 8. Texture wrap:clamp to border" << std::endl;
	std::cout << " 9. Texture filter:linear" << std::endl;
	std::cout << "10. Texture filter:nearest" << std::endl;
	std::cout << "11. Texture color ----------[Example05.cpp]" << std::endl;
	std::cout << "12. Texture invert" << std::endl;
	std::cout << "13. Texture grayscale" << std::endl;
	std::cout << "14. Texture add" << std::endl;
	std::cout << "15. Texture multiply" << std::endl;
	std::cout << "16. Texture lerp" << std::endl;
	std::cout << "17. Simple Mesh ------------[Example06.cpp]" << std::endl;
	std::cout << "18. Shader -----------------[Example07.cpp]" << std::endl;
	std::cout << "19. Transform --------------[Example08.cpp]" << std::endl;
	std::cout << "20. MVP:Perspective --------[Example09.cpp]" << std::endl;
	std::cout << "21. MVP:Ortho1" << std::endl;
	std::cout << "22. MVP:Ortho2" << std::endl;
	std::cout << "23. Scene ------------------[Example10.cpp]" << std::endl;
	std::cout << "24. Obj Loading ------------[Example11.cpp]" << std::endl;
	std::cout << "25. Shader - Color ---------[Example12.cpp]" << std::endl;
	std::cout << "26. Shader - Lambert" << std::endl;
	std::cout << "27. Shader - HalfLambert" << std::endl;
	std::cout << "28. Shader - Rim" << std::endl;
	std::cout << "29. Shader - Outline" << std::endl;
	std::cout << "30. Shader - Thickness" << std::endl;
	std::cout << "31. Bezier Curve -----------[Example13.cpp]" << std::endl;
	std::cout << "32. Bezier Spline" << std::endl;
	std::cout << "33. Hermite Curve" << std::endl;
	std::cout << "34. Hermite Spline" << std::endl;
	std::cout << "Q. Quit" << std::endl;
	std::cout << "==========================" << std::endl;
}

template <typename T>
void RunExample()
{
	T instance{};
	instance.Run();
}

template <typename Example04, UvType uvType, int wrapType, int filterType>
void RunExample()
{
	Example04 instance{};
	instance.RunWithParam(uvType, wrapType, filterType);
}

template <typename Example05, typename Example05::ShaderType shaderType>
void RunExample()
{
	Example05 instance{};
	instance.RunWithParam(shaderType);
}

template <typename Example09, typename Example09::ProjectionType projectionType>
void RunExample()
{
	Example09 instance{};
	instance.RunWithParam(projectionType);
}

template <typename Example12, typename Example12::BasicShaderType shaderType>
void RunExample()
{
	Example12 instance{};
	instance.RunWithParam(shaderType);
}

template <typename Example13, typename Example13::CurveType curveType>
void RunExample()
{
	Example13 instance{};
	instance.RunWithParam(curveType);
}

int main()
{
	PrintMenu();

	std::vector<std::function<void()>> examples
	{
		nullptr,
		
		RunExample<Example01>,
		
		RunExample<Example02>,
		
		RunExample<Example03>,
		
		RunExample<Example04, UvType::Fit, GL_REPEAT, GL_NEAREST>,
		RunExample<Example04, UvType::Smaller, GL_REPEAT, GL_NEAREST>,
		RunExample<Example04, UvType::Smaller, GL_CLAMP_TO_EDGE, GL_NEAREST>,
		RunExample<Example04, UvType::Smaller, GL_MIRRORED_REPEAT, GL_NEAREST>,
		RunExample<Example04, UvType::Smaller, GL_CLAMP_TO_BORDER, GL_NEAREST>,
		RunExample<Example04, UvType::Bigger, GL_REPEAT, GL_LINEAR>,
		RunExample<Example04, UvType::Bigger, GL_REPEAT, GL_NEAREST>,
		
		RunExample<Example05, Example05::ShaderType::TextureColor>,
		RunExample<Example05, Example05::ShaderType::Invert>,
		RunExample<Example05, Example05::ShaderType::Grayscale>,
		RunExample<Example05, Example05::ShaderType::Add>,
		RunExample<Example05, Example05::ShaderType::Multiply>,
		RunExample<Example05, Example05::ShaderType::Lerp>,
		
		RunExample<Example06>,
		
		RunExample<Example07>,
		
		RunExample<Example08>,
		
		RunExample<Example09, Example09::ProjectionType::Perspective>,
		RunExample<Example09, Example09::ProjectionType::Ortho1>,
		RunExample<Example09, Example09::ProjectionType::Ortho2>,
		
		RunExample<Example10>,
		
		RunExample<Example11>,
		
		RunExample<Example12, Example12::BasicShaderType::Color>,
		RunExample<Example12, Example12::BasicShaderType::Lambert>,
		RunExample<Example12, Example12::BasicShaderType::HalfLambert>,
		RunExample<Example12, Example12::BasicShaderType::Rim>,
		RunExample<Example12, Example12::BasicShaderType::Outline>,
		RunExample<Example12, Example12::BasicShaderType::Thickness>,

		RunExample<Example13, Example13::CurveType::BezierCurve>,
		RunExample<Example13, Example13::CurveType::BezierSpline>,
		RunExample<Example13, Example13::CurveType::HermiteCurve>,
		RunExample<Example13, Example13::CurveType::HermiteSpline>,
	};

	bool isRunning = true;
	while (isRunning)
	{
		std::string input{};
		std::cin >> input;

		if (input == "0")
		{
			system("cls");
			PrintMenu();
		}
		else if (input >= "1" && input <= "99")
		{
			int number = std::stoi(input);
			if (number < examples.size())
			{
				examples[number]();
			}
			else
			{
				std::cout << "Wrong example index : " << number << std::endl;
			}
		}
		else if (input == "q" || input == "Q")
		{
			isRunning = false;
		}
		else
		{
			std::cout << "Wrong command..." << std::endl;
		}
	}

	return 0;
}
