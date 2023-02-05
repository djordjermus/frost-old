#pragma once
namespace frost
{
	class eventData
	{
	public:
		eventData() = default;
		virtual ~eventData() = default;
	};

	template<class TSender, class TData>
	class eventHandler
	{
	public:
		using sender_type	= TSender;
		using data_type		= TData;

		eventHandler() = default;
		virtual ~eventHandler() = default;
		virtual void handle(TSender sender, TData& e) { /* STUB METHOD */ }
	};

}