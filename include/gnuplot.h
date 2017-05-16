#pragma once

#include <cstdio>
#include <string>
#include <memory>

namespace gnuplot
{

class graph final
{
public:
	graph()
		: graph("gnuplot")
	{
	}

	graph(const std::string& _path)
	{
		//m_file = std::shared_ptr<FILE>(_popen((_path).c_str(), "w"), _pclose);
		m_file = std::shared_ptr<FILE>(_popen((_path + " -persist").c_str(), "w"), _pclose);
	}

	void close()
	{
		m_file.reset();
	}

	void flush() const
	{
		fflush(m_file.get());
	}

	void command(const std::string& _command) const
	{
		fprintf(m_file.get(), "%s\n", _command.c_str());
		flush();
	}

	void reset() const
	{
		command("reset");
	}

	void replot() const
	{
		command("replot");
	}

	void set_title(const std::string& _title) const
	{
		fprintf(m_file.get(), "set title '%s'\n", _title.c_str());
		flush();
	}

	void set_x_range(double _minimum, double _maximum) const
	{
		fprintf(m_file.get(), "set xrange [%lf:%lf]\n", _minimum, _maximum);
		flush();
	}

	void set_y_range(double _minimum, double _maximum) const
	{
		fprintf(m_file.get(), "set yrange [%lf:%lf]\n", _minimum, _maximum);
		flush();
	}

	void set_autoscale() const
	{
		command("set autoscale");
	}

	void set_x_label(const std::string& _name) const
	{
		fprintf(m_file.get(), "set xlabel '%s'\n", _name.c_str());
		flush();
	}

	void set_y_label(const std::string& _name) const
	{
		fprintf(m_file.get(), "set ylabel '%s'\n", _name.c_str());
		flush();
	}

	bool is_opened() const
	{
		return m_file.get() != nullptr;
	}

private:
	std::shared_ptr<FILE> m_file;
};

}