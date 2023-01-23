#pragma once
namespace frost {
	template<class T, class... Us>
	class tuple : protected tuple<Us...> 
	{
		template<class T1, class T2>
		static constexpr bool same_type = false;
		template<class Type>
		static constexpr bool same_type<Type, Type> = true;

	public:

		template<unsigned long long index>
		auto& get() 
		{
			if constexpr (index == 0) return _val;
			else return this->tuple<Us...>::get<index - 1>();
		}

		template<class SearchT, unsigned long long index>
		SearchT& get() 
		{
			if constexpr (same_type<T, SearchT>)
				if constexpr (index == 0) return _val;
				else return this->tuple<Us...>::get<SearchT, index - 1>();
			else return this->tuple<Us...>::get<SearchT, index>();
		}

	private:
		T _val;
	};

	template<class T>
	class tuple<T> 
	{
		template<class T1, class T2>
		static constexpr bool same_type = false;
		template<class Type>
		static constexpr bool same_type<Type, Type> = true;

	public:

		template<unsigned long long index>
		auto& get() 
		{
			static_assert(
				index == 0, 
				"tuple<...>::get<index> - index is out of bounds.");

			if constexpr (index == 0)
				return _val;
		}

		template<class SearchT, unsigned long long index>
		SearchT& get() 
		{
			static_assert(
				same_type<SearchT, T> && index == 0, 
				"tuple<...>::get<SearchT, index> - Requested element does not exist");

			if constexpr (same_type<T, SearchT> && index == 0)
				if constexpr (index == 0) return _val;
		}

	private:
		T _val;
	};
}