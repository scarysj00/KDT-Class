#pragma once
struct FDeleteAccountTask
{
	FDeleteAccountTask();
	FDeleteAccountTask(const FDeleteAccountTask&) = delete;
	FDeleteAccountTask(const FDeleteAccountTask&&) = delete;
	FDeleteAccountTask& operator=(const FDeleteAccountTask&) = delete;
};

