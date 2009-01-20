/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _API_BINDING_H_
#define _API_BINDING_H_

#include <kroll/kroll.h>
#include <map>
#include <vector>
#include <string>

namespace kroll
{
	typedef std::vector<SharedBoundMethod*> EventRecords;

	struct BoundEventEntry
	{
		SharedBoundMethod method;
		std::string event;
	};

	enum LogSeverity
	{
		KR_LOG_DEBUG = 1,
		KR_LOG_INFO = 2,
		KR_LOG_ERROR = 3,
		KR_LOG_WARN = 4
	};

	class APIBinding : public StaticBoundObject
	{
	public:
		APIBinding(SharedBoundObject global);
		virtual ~APIBinding();

		void Log(int& severity, std::string& message);
		int Register(std::string& event, SharedBoundMethod callback);
		void Unregister(int ref);
		void Fire(std::string& event, SharedValue data);

	private:
		void _Set(const ValueList& args, SharedValue result);
		void _Get(const ValueList& args, SharedValue result);
		void _Log(const ValueList& args, SharedValue result);
		void _Register(const ValueList& args, SharedValue result);
		void _Unregister(const ValueList& args, SharedValue result);
		void _Fire(const ValueList& args, SharedValue result);

		// void Unload(const ValueList& args, Value *result);
		// void Reload(const ValueList& args, Value *result);
		// void Modules(const ValueList& args, Value *result);

		std::map<std::string, EventRecords> registrations;
		std::map<int, BoundEventEntry> registrationsById;
		int record;
		SharedBoundObject global;

		int GetNextRecord();
	};
}

#endif