#include "Core/EngineTypes.h"
#include "Utilities/Singleton.inl"

#ifndef CXC_PARSER_H
#define CXC_PARSER_H
#define PARSER_ERROR -1

namespace cxc{

	class CXC_ENGINECORE_API Parser final 
	{

	public:

		Parser();
		~Parser();

		Parser(const Parser &) = delete;
		Parser& operator=(const Parser &) = delete;

		Parser(const Parser &&) = delete;
		Parser& operator=(const Parser &&) = delete;

	// public interface
	public:

		bool ParseScript(const std::string &script_file) noexcept;

		bool GetTokensAttribSet(const std::string &token,std::vector<std::string> &ret) const noexcept;

		int GetErrorLines() const noexcept;

		bool isLoaded() const noexcept;

	public:

		// <Token name , Attribute value sets>
		std::unordered_map<std::string, std::vector<std::string>> m_TokenAttribs;

		// Token tree
		std::unordered_map<std::string, std::shared_ptr<TokenTree>> m_TokenTree;

	private:

		int error_lines;

		bool Load;

		// if failed, return the number of lines that error occurs
		int tokenize(const std::string &script) noexcept;

		// Removing the space in the string
		void trim(std::string &s);

		// remove '\' in the string
		void AttribPreProcessing(std::string &attrib);

	};
}

#endif // CXC_PARSER_H