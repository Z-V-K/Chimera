#pragma once

template< typename T >
std::string hexify(T i)
{
	std::stringbuf buf;
	std::ostream os(&buf);


	os << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2)
		<< std::hex << i;

	return buf.str().c_str();
}