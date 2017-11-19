/*
 * Debugging function - conditional printf and hex dump. Driver wrappers can
 * use these for debugging purposes.
 */

enum {
    MSG_EXCESSIVE, MSG_MSGDUMP, MSG_DEBUG, MSG_INFO, MSG_WARNING, MSG_ERROR
};
