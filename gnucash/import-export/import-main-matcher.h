/********************************************************************\
 * import-main-matcher.h - Transaction matcher main window          *
 *                                                                  *
 * Copyright (C) 2002 Benoit Grégoire <bock@step.polymtl.ca>        *
 * Copyright (C) 2002 Christian Stimming                            *
 * Copyright (C) 2012 Robert Fewell                                 *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, contact:                        *
 *                                                                  *
 * Free Software Foundation           Voice:  +1-617-542-5942       *
 * 51 Franklin Street, Fifth Floor    Fax:    +1-617-542-2652       *
 * Boston, MA  02110-1301,  USA       gnu@gnu.org                   *
\********************************************************************/
/** @addtogroup Import_Export
    @{ */
/**@file import-main-matcher.h
   @brief Transaction matcher main window
   @author Copyright (C) 2002 Benoit Grégoire
   @author Christian Stimming
*/

#ifndef GNC_IMPORT_MAIN_MATCHER_H
#define GNC_IMPORT_MAIN_MATCHER_H

#include "Transaction.h"
#include "import-backend.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _main_matcher_info GNCImportMainMatcher;

typedef void (*GNCTransactionProcessedCB) (GNCImportTransInfo *trans_info,
                                           gboolean imported,
                                           gpointer user_data);

/** Create a new generic transaction dialog window and return it.
 *
 * @param parent The parent GtkWidget. May be NULL.
 *
 * @param heading The heading label in the Importer window. May be NULL.
 *
 * @param all_from_same_account Set this to TRUE if ALL the
 * transaction that will be added with gnc_gen_trans_list_add_trans
 * are from the same source account.  This will cause the account
 * column to be hidden.
 *
 * @param match_date_hardlimit The number of days that a matching
 * split may differ from the given transaction before it is discarded
 * immediately. In other words, any split that is more distant from
 * the given transaction than this match_date_hardlimit days will be
 * ignored altogether. For use cases without paper checks (e.g. HBCI),
 * values like 14 (days) might be appropriate, whereas for use cases
 * with paper checks (e.g. OFX, QIF), values like 42 (days) seem more
 * appropriate.
 *
 @param show_all if true, all widgets are shown
 *
 * @return A pointer to the GNCImportMainMatcher which has been setup.
*/
GNCImportMainMatcher *gnc_gen_trans_list_new (GtkWidget *parent,
                                              const gchar* heading,
                                              bool all_from_same_account,
                                              gint match_date_hardlimit,
                                              bool show_all);



/**  Add the Transaction matcher to an existing page of an assistant.
 *   Must be called with the parent widget, ie. a vbox that the
 *   transaction matcher will be packed into. The data structure
 *   GNCImportMainMatcher is returned.
 *
 * @param parent The parent widget
 *
 * @param assistant_page The parent widget. This is the place the
 * transaction matcher will be packed into.
 *
 * @param heading The heading label in the Importer window. May be NULL.
 *
 * @param all_from_same_account Set this to TRUE if ALL the
 * transaction that will be added with gnc_gen_trans_list_add_trans
 * are from the same source account.  This will cause the account
 * column to be hidden.
 *
 * @param match_date_hardlimit The number of days that a matching
 * split may differ from the given transaction before it is discarded
 * immediately. In other words, any split that is more distant from
 * the given transaction than this match_date_hardlimit days will be
 * ignored altogether. For use cases without paper checks (e.g. HBCI),
 * values like 14 (days) might be appropriate, whereas for use cases
 * with paper checks (e.g. OFX, QIF), values like 42 (days) seem more
 * appropriate.
 *
 * @return A pointer to the GNCImportMainMatcher which has been setup.
*/
GNCImportMainMatcher * gnc_gen_trans_assist_new (GtkWidget *parent,
                                                 GtkWidget *assistant_page,
                                                 const gchar* heading,
                                                 bool all_from_same_account,
                                                 gint match_date_hardlimit);


/**  This starts the import process for transaction from an assistant.
 *   assistant button callback.
 *
 * @param info. A pointer to the GNCImportMainMatcher structure
*/
void gnc_gen_trans_assist_start (GNCImportMainMatcher *info);


/**  This allows for the transaction help dialog to be started from the
 *   assistant button callback.
 *
 * @param button. The button widget clicked on in the call back.
 *
 * @param user_data. A pointer to a structure.
*/
void on_matcher_help_clicked (GtkButton *button, gpointer user_data);


/** Add transaction processed callback to the transaction importer.
 *
 * @param info The Transaction Importer to use.
 *
 * @param trans_processed_cb The callback function.
 */
void gnc_gen_trans_list_add_tp_cb (GNCImportMainMatcher *info,
                                   GNCTransactionProcessedCB trans_processed_cb,
                                   gpointer user_data);


/** Deletes the given object. */
void gnc_gen_trans_list_delete (GNCImportMainMatcher *info);

/** Add a newly imported Transaction to the Transaction Importer.
 *  The Importer takes over ownership of the passed transaction.
 *
 * @param gui The Transaction Importer to use.
 *
 * @param trans The Transaction to add.  The must contain at least one
 * split, and this split must have been associated with an account
 * Only the first split will be used for matching.  The transaction
 * must NOT be committed. The Importer takes over ownership of the
 * passed transaction.
 */
void gnc_gen_trans_list_add_trans (GNCImportMainMatcher *gui, Transaction *trans);


/** Add a newly imported Transaction to the Transaction Importer.
 *  The Importer takes over ownership of the passed transaction.
 *
 * @param gui The Transaction Importer to use.
 *
 * @param trans The Transaction to add.  The must contain at least one
 * split, and this split must have been associated with an account
 * Only the first split will be used for matching.  The transaction
 * must NOT be committed. The Importer takes over ownership of the
 * passed transaction.
 *
 * @param lsplit Struct with additional parameters that may be used to
 * generate the final split.
 */
void gnc_gen_trans_list_add_trans_with_split_data (GNCImportMainMatcher *gui,
                                                   Transaction *trans,
                                                   GNCImportLastSplitInfo *lsplit);


/** Add a newly imported Transaction to the Transaction Importer and provide an
 * external reference id for it.
 * The Importer takes over ownership of the passed transaction.
 *
 * @param gui The Transaction Importer to use.
 *
 * @param trans The Transaction to add.  The must contain at least one
 * split, and this split must have been associated with an account
 * Only the first split will be used for matching.  The transaction
 * must NOT be committed. The Importer takes over ownership of the
 * passed transaction.
 *
 * @param ref_id Reference id which links an external object to the transaction.
 */
void gnc_gen_trans_list_add_trans_with_ref_id (GNCImportMainMatcher *gui,
                                               Transaction *trans,
                                               guint32 ref_id);


/** Run this dialog and return only after the user pressed Ok, Cancel,
  or closed the window. This means that all actual importing will
  have been finished upon returning.
 * @param info A pointer to the GNCImportMainMatcher structure.
 * @return The boolean return value of the dialog run.
*/
bool gnc_gen_trans_list_run (GNCImportMainMatcher *info);


/** Returns the widget of this dialog.
 * @param info A pointer to the GNCImportMainMatcher structure.
 * @return A GtkWidget pointer to the dialog's widget.
 */
GtkWidget *gnc_gen_trans_list_widget (GNCImportMainMatcher *info);

/** Returns the append_text widget of this dialog.
 * @param info A pointer to the GNCImportMainMatcher structure.
 * @return A GtkWidget pointer to the append_text widget.
 */
GtkWidget *
gnc_gen_trans_list_append_text_widget (GNCImportMainMatcher *info);

/** Checks whether there are no transactions to match.
 * @param info A pointer to the GNCImportMainMatcher structure.
 * @return A boolean indicating whether the transaction list is empty.
 */
bool gnc_gen_trans_list_empty (GNCImportMainMatcher *info);

/** Shows widgets.
 * @param info A pointer to the GNCImportMainMatcher structure.
 */
void gnc_gen_trans_list_show_all (GNCImportMainMatcher *info);

/** Show and set the reconcile after close check button.
 * @param info A pointer to the GNCImportMainMatcher structure.
 * @param reconcile_after_close A bool that shows or hides the button.
 * @param active A bool to set or clear the check button.
 */
void gnc_gen_trans_list_show_reconcile_after_close_button (GNCImportMainMatcher *info,
                                                           bool reconcile_after_close,
                                                           bool active);
/** Returns the reconcile after close check button.
 * @param info A pointer to the GNCImportMainMatcher structure.
 * @return The check button.
 */
GtkWidget* gnc_gen_trans_list_get_reconcile_after_close_button (GNCImportMainMatcher *info);

#ifdef __cplusplus
}
#endif

#endif
/**@}*/
