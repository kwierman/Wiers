#ifndef WUtilities_h_
#define WUtilities_h_ 1

//---------------------------------------------------------------------
void signal_callback_handler(int signum);
static inline void print_stacktrace(unsigned int stack_depth = 100);
//---------------------------------------------------------------------

#define KJW_DEBUG std::cout<<__FILE__<<" : "<<__LINE__<<std::endl;

#endif //WUtilities_h_

