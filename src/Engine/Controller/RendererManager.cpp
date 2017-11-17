#include "RendererManager.h"

namespace cxc {

	RendererManager::RendererManager()
		: FontShader(),SpriteShader(),
		m_LightPos(glm::vec3(0,1500,1500))
	{
	}

	RendererManager::~RendererManager()
	{

	}

	void RendererManager::releaseResources() noexcept
	{
		auto programid = GetShaderProgramID(CXC_SPRITE_SHADER_PROGRAM);
		if (programid)
			glDeleteProgram(programid);
	}

	void RendererManager::DrawCoordinateAxis() noexcept
	{

		glLineWidth(10);
		glBegin(GL_LINES);
		// draw line for x axis
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(10.0, 0.0, 0.0);
		// draw line for y axis
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);
		// draw line for Z axis
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 10.0);
		glEnd();

		glFlush();
	}

	GLint RendererManager::GetShaderProgramID(ShaderType Type) const noexcept
	{
		switch (Type)
		{
		case CXC_SPRITE_SHADER_PROGRAM:
			return SpriteShader.ProgramID;
			break;
		case CXC_FONT_SHADER_PROGRAM:
			return FontShader.ProgramID;
			break;
		default:
			return -1;
			break;
		}
	}

	const glm::vec3 &RendererManager::GetLightPos() const noexcept
	{
		return m_LightPos;
	}

	void RendererManager::SetLightPos(const glm::vec3 &pos) noexcept
	{
		m_LightPos = pos;
	}

	GLboolean RendererManager::isShaderLoaded(ShaderType Type) const noexcept
	{
		switch (Type)
		{
		case CXC_SPRITE_SHADER_PROGRAM:
			if (SpriteShader.ProgramID)
				return GL_TRUE;
			else
				return GL_FALSE;
			break;
		case CXC_FONT_SHADER_PROGRAM:
			if (FontShader.ProgramID)
				return GL_TRUE;
			else
				return GL_FALSE;
			break;
		default:
			return GL_FALSE;
			break;
		}
	}

	GLboolean RendererManager::BindShaderWithExistingProgram(ShaderType Type,
															const std::string &vertex_path,
															const std::string &fragment_path) noexcept
	{
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		GLint ProgramID;

		std::string VertexShaderCode, FragmentShaderCode;

		if (LoadVertexShader(vertex_path, VertexShaderCode) == GL_FALSE)
			return GL_FALSE;

		if (LoadFragmentShader(fragment_path, FragmentShaderCode) == GL_FALSE)
			return GL_FALSE;

		if (CompileShader(VertexShaderID, VertexShaderCode) != GL_TRUE)
			return GL_FALSE;

		if (CompileShader(FragmentShaderID, FragmentShaderCode) != GL_TRUE)
			return GL_FALSE;

		switch (Type)
		{
		case CXC_SPRITE_SHADER_PROGRAM:
			ProgramID = SpriteShader.ProgramID;
			break;
		case CXC_FONT_SHADER_PROGRAM:
			ProgramID = FontShader.ProgramID;
			break;
		default:
			return GL_FALSE;
			break;
		}

		if (LinkVertexAndFragmentShader(ProgramID, VertexShaderID, FragmentShaderID) != GL_TRUE)
			return GL_FALSE;

		return GL_TRUE;
	}

	void RendererManager::SetProgramID(ShaderType Type,GLint ProgramID) noexcept
	{
		switch (Type)
		{
		case CXC_SPRITE_SHADER_PROGRAM:
			SpriteShader.ProgramID = ProgramID;
			break;
		case CXC_FONT_SHADER_PROGRAM:
			FontShader.ProgramID = ProgramID;
			break;
		default:
			break;
		}
	}

	GLboolean RendererManager::GetVertexShaderArray(ShaderType Type, std::vector<GLint> &VertexArray) const noexcept
	{
		switch (Type)
		{
		case CXC_SPRITE_SHADER_PROGRAM:
			if (SpriteShader.ProgramID)
			{
				VertexArray = SpriteShader.VertexShader;
				return GL_TRUE;
			}
			else
				return GL_FALSE;
			break;
		case CXC_FONT_SHADER_PROGRAM:
			if (FontShader.ProgramID)
			{
				VertexArray = FontShader.VertexShader;
				return GL_TRUE;
			}
			else
				return GL_FALSE;
			break;
		default:
			return GL_FALSE;
		}
	}

	GLboolean RendererManager::GetFragmentShaderArray(ShaderType Type, std::vector<GLint> &FragmentArray) const noexcept
	{
		switch (Type)
		{
		case CXC_SPRITE_SHADER_PROGRAM:
			if (SpriteShader.ProgramID)
			{
				FragmentArray = SpriteShader.FragmentShader;
				return GL_TRUE;
			}
			else
				return GL_FALSE;
			break;
		case CXC_FONT_SHADER_PROGRAM:
			if (FontShader.ProgramID)
			{
				FragmentArray = FontShader.FragmentShader;
				return GL_TRUE;
			}
			else
				return GL_FALSE;
			break;
		default:
			return GL_FALSE;
		}
	}

	GLboolean RendererManager::CheckCompilationStatus(GLuint ShaderID) const noexcept
	{
		GLint ret;
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &ret);

		return static_cast<GLboolean>(ret);
	}

	GLboolean RendererManager::CheckLinkageStatus(GLuint ProgramID) const noexcept
	{
		GLint ret;
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &ret);

		return static_cast<GLboolean>(ret);
	}

	GLboolean RendererManager::LoadVertexShader(const std::string &vertex_file_path, std::string &vertex_shader_code) const
	{
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);

		if (VertexShaderStream.is_open())
		{
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else
			return GL_FALSE;

		vertex_shader_code = std::move(VertexShaderCode);

		return GL_TRUE;
	}

	GLboolean RendererManager::LoadFragmentShader(const std::string &fragment_file_path, std::string &fragment_shader_code) const
	{
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);

		if (FragmentShaderStream.is_open())
		{
			std::string line = "";
			while (getline(FragmentShaderStream, line))
				FragmentShaderCode += "\n" + line;
			FragmentShaderStream.close();
		}
		else
		{
			std::cout << "can not open fragment shader file\n" << std::endl;
			return GL_FALSE;
		}

		fragment_shader_code = std::move(FragmentShaderCode);

		return GL_TRUE;
	}

	GLboolean RendererManager::CompileShader(GLuint ShaderID, const std::string &SourceCode) const
	{
		const char *VertexSourcePointer = SourceCode.c_str();
		glShaderSource(ShaderID, 1, &VertexSourcePointer, nullptr);
		glCompileShader(ShaderID);

		if (CheckCompilationStatus(ShaderID) != GL_TRUE)
			return GL_FALSE;
		else
			return GL_TRUE;
	}

	GLboolean RendererManager::LinkVertexAndFragmentShader(GLuint ProgramID, GLuint VertexShaderID, GLuint FragmentShaderID) const
	{
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		if (CheckLinkageStatus(ProgramID) != GL_TRUE)
			return GL_FALSE;
		else
			return GL_TRUE;
	}

	void RendererManager::CreateProgram(ShaderType Type,ProgramStruct &program) noexcept
	{
		if (!program.ProgramID) return;

		switch (Type)
		{
		case CXC_SPRITE_SHADER_PROGRAM:
			SpriteShader = program;
			break;
		case CXC_FONT_SHADER_PROGRAM:
			FontShader = program;
			break;
		default:
			break;
		}
	}

	GLboolean RendererManager::CreateShaderProgram(ProgramStruct &ret,
												const std::string &vertex_file_path,
												const std::string &fragment_file_path)
	{
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		GLuint ProgramID = glCreateProgram();

		std::string VertexShaderCode, FragmentShaderCode;

		if (LoadVertexShader(vertex_file_path, VertexShaderCode) == GL_FALSE)
			return GL_FALSE;

		if (LoadFragmentShader(fragment_file_path, FragmentShaderCode) == GL_FALSE)
			return GL_FALSE;

		if (CompileShader(VertexShaderID, VertexShaderCode) != GL_TRUE)
			return GL_FALSE;

		if (CompileShader(FragmentShaderID, FragmentShaderCode) != GL_TRUE)
			return GL_FALSE;

		if (LinkVertexAndFragmentShader(ProgramID, VertexShaderID, FragmentShaderID) != GL_TRUE)
			return GL_FALSE;

		ret.ReConstruct(ProgramID,VertexShaderID,FragmentShaderID);
		
		return GL_TRUE;
	}

	void RendererManager::SetShaderStruct(ShaderType type, ProgramStruct &shader_struct) noexcept
	{
		if (type == CXC_SPRITE_SHADER_PROGRAM)
		{
			SpriteShader = shader_struct;
		}
		else
		{
			FontShader = shader_struct;
		}
	}

	void RendererManager::BindLightingUniforms() const
	{

		GLuint LightID = glGetUniformLocation(SpriteShader.ProgramID, "LightPosition_worldspace");
		glUniform3f(LightID, m_LightPos.x, m_LightPos.y, m_LightPos.z);
		
	}
}