
//////////////////////////////////////////////////////////

#ifndef SHORTEST_PATH_DETAILS_HPP
#define SHORTEST_PATH_DETAILS_HPP

//////////////////////////////////////////////////////////

#include "../kernel/kernel.hpp"

//////////////////////////////////////////////////////////

#define SHORTEST_PATH_DETAILS_EXPORT C_IS_EASY_EXPORT

//////////////////////////////////////////////////////////

namespace c_is_easy
{
	namespace graph
	{
		namespace shortest_path
		{
			namespace details
			{
				using vertex_index		= unsigned int;
				using vertex_distance	= long long;
				using graph_distances	= std::vector<vertex_distance>;
				constexpr unsigned int infinity = static_cast<unsigned int>(-1);

				struct SHORTEST_PATH_DETAILS_EXPORT break_search { };

				//template <typename Graph>
				//class SHORTEST_PATH_DETAILS_EXPORT algorithms_adapter
				//{
				//	using Vertex = typename boost::graph_traits<Graph>::vertex_descriptor;
				//public:

				//	virtual void make_boost_graph()

				//	virtual vertex_index get_vertex_index	(const Graph& graph, const Vertex& vertex) = 0;
				//	virtual vertex_index get_vertex_by_index(const Graph& graph, const Vertex& vertex) = 0;

				//};

				template <typename Graph>
				vertex_index SHORTEST_PATH_DETAILS_EXPORT get_vertex_index(const Graph& graph,
					const typename boost::graph_traits<Graph>::vertex_descriptor& vertex)
				{
					return ((vertex_index)vertex); // temp
				}
				template <typename Graph>
				typename boost::graph_traits<Graph>::vertex_descriptor	SHORTEST_PATH_DETAILS_EXPORT
					get_vertex_by_index(const Graph& graph, vertex_index index)
				{
					using Traits = typename boost::graph_traits<Graph>;
					using Vertex = typename Traits::vertex_descriptor;

					return ((Vertex)index); // temp
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////

#endif // !SHORTEST_PATH_DETAILS_HPP

//////////////////////////////////////////////////////////
