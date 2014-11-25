/*
 * replay-database.h
 *
 * interface for a replay database for packet security
 *
 * David A. McGrew
 * Cisco Systems, Inc.
 */


#ifndef REPLAY_DB_H
#define REPLAY_DB_H

#include "integers.h"         /* for uint32_t     */
#include "datatypes.h"        /* for v128_t       */
#include "err.h"              /* for srtp_err_status_t */

/*
 * if the ith least significant bit is one, then the packet index
 * window_end-i is in the database
 */

typedef struct {
    uint32_t window_start; /* packet index of the first bit in bitmask */
    v128_t bitmask;
} srtp_rdb_t;

#define rdb_bits_in_bitmask (8 * sizeof(v128_t))

/*
 * srtp_rdb_init
 *
 * initalizes rdb
 *
 * returns srtp_err_status_ok on success, srtp_err_status_t_fail otherwise
 */
srtp_err_status_t srtp_rdb_init(srtp_rdb_t *rdb);


/*
 * srtp_rdb_check
 *
 * checks to see if index appears in rdb
 *
 * returns srtp_err_status_fail if the index already appears in rdb,
 * returns srtp_err_status_ok otherwise
 */
srtp_err_status_t srtp_rdb_check(const srtp_rdb_t *rdb, uint32_t rdb_index);

/*
 * srtp_rdb_add_index
 *
 * adds index to srtp_rdb_t (and does *not* check if index appears in db)
 *
 * returns srtp_err_status_ok on success, srtp_err_status_fail otherwise
 *
 */
srtp_err_status_t srtp_rdb_add_index(srtp_rdb_t *rdb, uint32_t rdb_index);

/*
 * the functions srtp_rdb_increment() and srtp_rdb_get_value() are for use by
 * senders, not receivers - DO NOT use these functions on the same
 * srtp_rdb_t upon which srtp_rdb_add_index is used!
 */


/*
 * srtp_rdb_increment(db) increments the sequence number in db, if it is
 * not too high
 *
 * return values:
 *
 *    srtp_err_status_ok            no problem
 *    srtp_err_status_key_expired   sequence number too high
 *
 */
srtp_err_status_t srtp_rdb_increment(srtp_rdb_t *rdb);

/*
 * srtp_rdb_get_value(db) returns the current sequence number of db
 */
uint32_t srtp_rdb_get_value(const srtp_rdb_t *rdb);


#endif /* REPLAY_DB_H */
