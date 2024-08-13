#pragma once

template<typename... Msg>
void PrintThreadMsg(int32 rgb, Msg... msgs)
{
	std::stringstream full_message;
	full_message << std::this_thread::get_id();
	int64 tid = std::stoull(full_message.str().c_str());
	full_message.str("");
	full_message.str(std::string());

	// string format: <[thread_id]: msgs...>
	std::string strformat = std::format("\033[38;5;{}m[{:08}] ", rgb, tid); // \033[38;5;{rgb code}m 

	full_message << strformat;
	(full_message << ... << msgs); // using fold expression
	printf(full_message.str().c_str());
}