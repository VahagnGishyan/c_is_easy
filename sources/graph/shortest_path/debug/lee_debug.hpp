
//////////////////////////////////////////////////////////

#ifndef SHORTEST_PATH_LEE_DEBUG_HPP
#define SHORTEST_PATH_LEE_DEBUG_HPP

//////////////////////////////////////////////////////////

#include "../details/lee_details.hpp"
#include "../shortest_path_lee.hpp"

//////////////////////////////////////////////////////////

#define SHORTEST_PATH_LEE_DEBUG_EXPORT C_IS_EASY_EXPORT

//////////////////////////////////////////////////////////

namespace c_is_easy
{
	namespace graph
	{
		namespace shortest_path
		{
			namespace debug
			{
				template <typename Graph>
				class SHORTEST_PATH_LEE_DEBUG_EXPORT debug_log_lee_visitor : public default_lee_visitor<Graph>
				{
				private:
					using Traits = typename boost::graph_traits<Graph>;
					using Vertex = typename Traits::vertex_descriptor;
					using VertexDistance = shortest_path::details::vertex_distance;
					using Distances = shortest_path::details::graph_distances;

					//////////////////////////////////////////////////////////////////////////////////////////////////

				public:
					debug_log_lee_visitor(const Graph& graph, const Vertex& start, const Vertex& end,
						Distances& distances, std::ostream& file)
						: shortest_path::default_lee_visitor<Graph>(graph, start, end, distances),
						m_log_file(file) { }

					void examine_vertex(const Vertex& vertex, const Graph& graph) override
					{
						shortest_path::default_lee_visitor<Graph>::examine_vertex(vertex, graph);
						std::cout << std::endl;
						std::cout << "\tVertex(" << shortest_path::details::get_vertex_index(graph, vertex) << ") :: ";
					}
					void discover_vertex(const Vertex& vertex, const Graph& graph) override
					{
						if ((*(this->m_active)) == vertex) return;
						std::cout << shortest_path::details::get_vertex_index(graph, vertex) << " "; // for test
						shortest_path::default_lee_visitor<Graph>::discover_vertex(vertex, graph);
					}

				public:
					void start()
					{
						std::cout << std::endl;
						std::cout << "lee\n{ ";
					}
					void end()
					{
						std::cout << std::endl << "}" << std::endl;
						std::cout << std::endl;
					}
				private:

					std::ostream& m_log_file;
				};

				using short_path = std::vector<details::vertex_index>;

				template <class Graph>
				const typename boost::graph_traits<Graph>::vertex_descriptor SHORTEST_PATH_LEE_DEBUG_EXPORT
					get_min_location(const Graph& graph,
						const typename boost::graph_traits<Graph>::vertex_descriptor& loc,
						const typename boost::graph_traits<Graph>::vertex_descriptor& end,
						const shortest_path::details::graph_distances& distances)
				{
					using Traits = typename boost::graph_traits<Graph>;
					using Vertex = typename Traits::vertex_descriptor;
					using AdjacencyItr = typename Traits::adjacency_iterator;

					AdjacencyItr vitr, vend;
					boost::tie(vitr, vend) = boost::adjacent_vertices(loc, graph);
					if ((*vitr) == end) return (end);

					Vertex min_loc_index = shortest_path::details::get_vertex_index(graph, (*vitr));
					++vitr;
					while (vitr != vend)
					{
						if ((*vitr) == end) return (end);
						auto vindex = shortest_path::details::get_vertex_index(graph, *vitr);
						if (distances[min_loc_index] > distances[vindex]) min_loc_index = vindex;
						++vitr;
					}

					return (shortest_path::details::get_vertex_index(graph, min_loc_index));
				}

				template <typename Graph>
				void SHORTEST_PATH_LEE_DEBUG_EXPORT search_shortest_path(const Graph& graph,
					typename boost::graph_traits<Graph>::vertex_descriptor start,
					typename boost::graph_traits<Graph>::vertex_descriptor end,
					const shortest_path::details::graph_distances& distances,
					short_path& path)
				{
					shortest_path::details::vertex_distance loc = end;

					if (distances[shortest_path::details::get_vertex_index(graph, end)] == details::infinity) return/*temp*/;

					path.push_back(shortest_path::details::get_vertex_index(graph, loc));
					while (loc != start)
					{
						loc = shortest_path::debug::get_min_location(graph, loc, start, distances);
						path.push_back(shortest_path::details::get_vertex_index(graph, loc));
					}

					std::reverse(path.begin(), path.end());
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////

#endif // !SHORTEST_PATH_LEE_DEBUG_HPP

//////////////////////////////////////////////////////////
