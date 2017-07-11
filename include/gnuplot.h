#pragma once

#include <cstdio>
#include <string>
#include <vector>
#include <memory>

namespace gnuplot
{

enum class style
{
	lines,
	points,
	lines_points,
	impulses,
	dots,
	steps,
	fsteps,
	histeps,
	boxes,
	filled_curves_x1,
	filled_curves_y1,
	filled_curves_closed,
};

using plot = std::vector<double>;

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

	void save()
	{

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

	void reset()
	{
		command("reset");
	}

	void replot() const
	{
		command("replot");
	}

	void title(const std::string& _title) const
	{
		fprintf(m_file.get(), "set title '%s'\n", _title.c_str());
		flush();
	}

	void unset_key()
	{
		command("unset key");
	}

	void x_range(double _minimum, double _maximum) const
	{
		fprintf(m_file.get(), "set xrange [%lf:%lf]\n", _minimum, _maximum);
		flush();
	}

	void y_range(double _minimum, double _maximum) const
	{
		fprintf(m_file.get(), "set yrange [%lf:%lf]\n", _minimum, _maximum);
		flush();
	}

	void autoscale() const
	{
		command("set autoscale");
	}

	void multiplot() const
	{
		command("set multiplot");
	}

	void style(const gnuplot::style& _style)
	{
		fprintf(m_file.get(), "set style function %s\n", get_style_name(_style).c_str());
		fprintf(m_file.get(), "set style data %s\n", get_style_name(_style).c_str());
		flush();
	}

	void line_width(size_t _width)
	{
		fprintf(m_file.get(), "set linetype 1 lw %d\n", _width);
		flush();
	}

	void line_color(const std::string& _color)
	{
		fprintf(m_file.get(), "set linetype 1 lc rgb '%s'\n", _color.c_str());
		flush();
	}

	void x_label(const std::string& _name) const
	{
		fprintf(m_file.get(), "set xlabel '%s'\n", _name.c_str());
		flush();
	}

	void y_label(const std::string& _name) const
	{
		fprintf(m_file.get(), "set ylabel '%s'\n", _name.c_str());
		flush();
	}

	void plot(const plot& _x, const plot& _y)
	{
		plot::const_iterator x_itr = _x.begin();
		plot::const_iterator y_itr = _y.begin();

		fprintf(m_file.get(), "plot '-'\n");

		while (x_itr != _x.end() && y_itr != _y.end())
		{
			fprintf(m_file.get(), "%lf %lf\n", *x_itr, *y_itr);
			x_itr++;
			y_itr++;
		}
		command("e");
	}

	bool is_opened() const
	{
		return m_file.get() != nullptr;
	}

	static const std::string& get_style_name(const gnuplot::style& _style)
	{
		static const std::string style_names[] =
		{
			"lines",
			"points",
			"lines_points",
			"impulses",
			"dots",
			"steps",
			"fsteps",
			"histeps",
			"boxes",
			"filled_curves_x1",
			"filled_curves_y1",
			"filled_curves_closed",
		};
		return style_names[static_cast<size_t>(_style)];
	}

private:
	std::shared_ptr<FILE> m_file;
};

}