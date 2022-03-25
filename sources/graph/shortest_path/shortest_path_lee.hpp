
//////////////////////////////////////////////////////////

#ifndef SHORTEST_PATH_LEE_HPP
#define SHORTEST_PATH_LEE_HPP

//////////////////////////////////////////////////////////

#include "details/lee_details.hpp"

//////////////////////////////////////////////////////////

#define SHORTEST_PATH_LEE_EXPORT C_IS_EASY_EXPORT

//////////////////////////////////////////////////////////

namespace c_is_easy
{
	namespace graph
	{
		namespace shortest_path
		{
			template <typename Graph>
			class SHORTEST_PATH_LEE_EXPORT default_lee_visitor : public boost::default_bfs_visitor
			{
			private:
				using Traits = typename boost::graph_traits<Graph>;
				using Vertex = typename Traits::vertex_descriptor;
				using VertexDistance = shortest_path::details::vertex_distance;
				using Distances = shortest_path::details::graph_distances;

				//////////////////////////////////////////////////////////////////////////////////////////////////

			public:
				default_lee_visitor(const Graph& graph, const Vertex& start, const Vertex& end, Distances& distances) :
					m_active(&start), m_start(start), m_end(end), m_distances(distances)
				{
					if (distances.size() != 0); // temp ????
					m_distances = std::move(Distances(graph.m_vertices.size(),
						VertexDistance(shortest_path::details::infinity))); // temp
					m_distances[shortest_path::details::get_vertex_index(graph, start)] = 0;
				}
				virtual ~default_lee_visitor() {}

				//////////////////////////////////////////////////////////////////////////////////////////////////

				virtual void examine_vertex(const Vertex& vertex, const Graph& graph)
				{
					m_active = &vertex;
				}
				virtual void discover_vertex(const Vertex& vertex, const Graph& graph)
				{
					if (*m_active == vertex) return;

					VertexDistance& vertex_distance = m_distances[shortest_path::details::
						get_vertex_index(graph, vertex)];
					const VertexDistance& active_distance = m_distances[shortest_path::details::
						get_vertex_index(graph, *m_active)];
					constexpr int edge_weight = 1;

					if (vertex == m_end)
					{
						vertex_distance = active_distance + edge_weight;
						throw shortest_path::details::break_search_lee(); // temp
					}

					if (vertex_distance > active_distance + edge_weight)
						vertex_distance = active_distance + edge_weight;
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////

				virtual const Distances&	get_distance() const
				{
					return (m_distances);
				}
				virtual const Vertex		get_start	() const
				{
					//return (std::pair<const tVertex&, const tVertex&>(m_start, m_end));
					return (m_start);
				}
				virtual const Vertex		get_end		() const
				{
					//return (std::pair<const tVertex&, const tVertex&>(m_start, m_end));
					return (m_end);
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////

			protected:
				Distances&		m_distances;
				const Vertex*	m_active;		// active vertex
				const Vertex	m_start;		// end vertex
				const Vertex	m_end;			// end vertex
			};

			//void SHORTEST_PATH_LEE_EXPORT lee(const Graph& graph, const Vertex& start, const Vertex& end);

			template <typename Graph, typename Visitor>
			void lee(const Graph& graph, Visitor& visitor)
			{
				try { boost::breadth_first_search(graph, visitor.get_start(), boost::visitor(visitor)); }
				catch (details::break_search_lee)				{/*log ???*/ }
				catch (shortest_path::details::break_search)	{/*log ???*/ }
				catch (...)										{/* temp, its error*/ }
				// class stop_search for try chatch
			}
		}
	}
}

//////////////////////////////////////////////////////////

#endif // !SHORTEST_PATH_LEE_HPP

//////////////////////////////////////////////////////////
