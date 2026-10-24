#include "core/core.h"
#include "ui/ui.h"

void setRealtimePriority() {
  // Get current process handle
  HANDLE hProcess = GetCurrentProcess();
  HANDLE hThread = GetCurrentThread();
    
  // Set process to real-time priority class
  if (!SetPriorityClass(hProcess, REALTIME_PRIORITY_CLASS)) {
     // Fallback to HIGH if REALTIME fails (needs admin)
    SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
  }
    
  // Set thread to time-critical
  SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
    
  // Prevent system sleep/CPU throttling
  SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
    
  // Set timer resolution to 1ms for better Sleep() precision
  timeBeginPeriod(1);
}

int main() {
  setRealtimePriority();
  // registerHotkeys();
  Root();

  return 0;
}