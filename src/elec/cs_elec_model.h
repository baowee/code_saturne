#ifndef __CS_ELEC_MODEL_H__
#define __CS_ELEC_MODEL_H__

/*============================================================================
 * General parameters management.
 *============================================================================*/

/*
  This file is part of Code_Saturne, a general-purpose CFD tool.

  Copyright (C) 1998-2015 EDF S.A.

  This program is free software; you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the Free Software
  Foundation; either version 2 of the License, or (at your option) any later
  version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
  Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Local headers
 *----------------------------------------------------------------------------*/

#include "cs_defs.h"

/*----------------------------------------------------------------------------*/

BEGIN_C_DECLS

/*=============================================================================
 * Macro definitions
 *============================================================================*/

/*============================================================================
 * Type definitions
 *============================================================================*/

/*----------------------------------------------------------------------------
 * Structure to read properties in dp_ELE
 *----------------------------------------------------------------------------*/

typedef struct {
  int     ngaz;
  int     npoint;
  double *th;
  double *ehgaz;
  double *rhoel;
  double *cpel;
  double *sigel;
  double *visel;
  double *xlabel;
  double *xkabel;
//  double *qespel;      /* Charge massique des especes  C/kg                 */
//  double *suscep;      /* Susceptibilite (relation champ - mobilite) m2/s/V */
} cs_data_elec_t;

/*----------------------------------------------------------------------------
 * Structure to read transformer parameters in dp_ELE
 *----------------------------------------------------------------------------*/

typedef struct {
  int     nbelec;
  int    *ielecc;
  int    *ielect;
  int    *ielecb;
  int     nbtrf;
  int     ntfref;
  int    *ibrpr;
  int    *ibrsec;
  double *tenspr;
  double *rnbs;
  double *zr;
  double *zi;
  double *uroff;
  double *uioff;
} cs_data_joule_effect_t;

/*----------------------------------------------------------------------------
 * Electrical model options descriptor
 *----------------------------------------------------------------------------*/

typedef struct {
  int     ieljou;
  int     ielarc;
  int     ielion;
  int     ixkabe;
  int     ntdcla;
  int     irestrike;
  double  restrike_point[3];
  double  crit_reca[5];
  int     ielcor;
  int     modrec;
  int     idreca;
  int    *izreca;
  double  couimp;
  double  pot_diff;
  double  puisim;
  double  coejou;
  double  elcou;
  double  srrom;
  char   *ficfpp;
} cs_elec_option_t;

/*============================================================================
 * Static global variables
 *============================================================================*/

/* Pointer to electrical model options structure */

extern const cs_elec_option_t        *cs_glob_elec_option;
extern const cs_data_elec_t          *cs_glob_elec_properties;
extern const cs_data_joule_effect_t  *cs_glob_transformer;

/* Constant for electrical models */

extern const double cs_elec_permvi;
extern const double cs_elec_epszer;

/*=============================================================================
 * Public function prototypes
 *============================================================================*/

/*----------------------------------------------------------------------------
 * Provide acces to cs_elec_option
 *----------------------------------------------------------------------------*/

cs_elec_option_t *
cs_get_glob_elec_option(void);

/*----------------------------------------------------------------------------
 * Provide acces to cs_glob_transformer
 *----------------------------------------------------------------------------*/

cs_data_joule_effect_t *
cs_get_glob_transformer(void);

/*----------------------------------------------------------------------------
 * Initialize structures for electrical model
 *----------------------------------------------------------------------------*/

void
cs_electrical_model_initialize(cs_int_t ielarc,
                               cs_int_t ieljou,
                               cs_int_t ielion);

/*----------------------------------------------------------------------------
 * Destroy structures for electrical model
 *----------------------------------------------------------------------------*/

void
cs_electrical_model_finalize(cs_int_t ielarc,
                             cs_int_t ieljou);

/*----------------------------------------------------------------------------
 * Specific initialization for electric arc
 *----------------------------------------------------------------------------*/

void
cs_electrical_model_specific_initialization(      cs_real_t *visls0,
                                                  cs_real_t *diftl0,
                                                  cs_int_t  *iconv,
                                                  cs_int_t  *istat,
                                                  cs_int_t  *idiff,
                                                  cs_int_t  *idifft,
                                                  cs_int_t  *idircl,
                                                  cs_int_t  *isca,
                                                  cs_real_t *blencv,
                                                  cs_real_t *sigmas,
                                                  cs_int_t  *iwarni,
                                            const cs_int_t   iihmpr);

/*----------------------------------------------------------------------------
 * Read properties file
 *----------------------------------------------------------------------------*/

void
cs_electrical_properties_read(cs_int_t ielarc,
                              cs_int_t ieljou);

/*----------------------------------------------------------------------------
 * compute specific electric arc fields
 *----------------------------------------------------------------------------*/

void
cs_compute_electric_field(const cs_mesh_t  *mesh,
                          int               call_id);

/*----------------------------------------------------------------------------
 * convert enthalpy-temperature
 *----------------------------------------------------------------------------*/

void
cs_elec_convert_h_t(cs_int_t   mode,
                    cs_real_t *ym,
                    cs_real_t *enthal,
                    cs_real_t *temp);

/*----------------------------------------------------------------------------
 * compute physical properties
 *----------------------------------------------------------------------------*/

void
cs_elec_physical_properties(const cs_mesh_t *mesh,
                            const cs_mesh_quantities_t *mesh_quantities);

/*----------------------------------------------------------------------------
 * compute source terms for energie and vector potential
 *----------------------------------------------------------------------------*/

void
cs_elec_source_terms(const cs_mesh_t *mesh,
                     const cs_mesh_quantities_t *mesh_quantities,
                     const cs_int_t   f_id,
                           cs_real_t *smbrs);

/*----------------------------------------------------------------------------
 * add variables fields
 *----------------------------------------------------------------------------*/

void
cs_elec_add_variable_fields(const cs_int_t *ielarc,
                            const cs_int_t *ieljou,
                            const cs_int_t *ielion,
                            const cs_int_t *iihmpr);

/*----------------------------------------------------------------------------
 * add properties fields
 *----------------------------------------------------------------------------*/

void
cs_elec_add_property_fields(const cs_int_t *ielarc,
                            const cs_int_t *ieljou,
                            const cs_int_t *ielion);

/*----------------------------------------------------------------------------
 * initialize electric fields
 *----------------------------------------------------------------------------*/

void
cs_elec_fields_initialize(const cs_mesh_t  *mesh,
                          cs_int_t          isuite);

/*----------------------------------------------------------------------------
 * scaling electric quantities
 *----------------------------------------------------------------------------*/

void
cs_elec_scaling_function(const cs_mesh_t *mesh,
                         const cs_mesh_quantities_t *mesh_quantities,
                                cs_real_t *dt);

/*----------------------------------------------------------------------------*/

void
CS_PROCF (elini1, ELINI1) (      cs_real_t *visls0,
                                 cs_real_t *diftl0,
                                 cs_int_t  *iconv,
                                 cs_int_t  *istat,
                                 cs_int_t  *idiff,
                                 cs_int_t  *idifft,
                                 cs_int_t  *idircl,
                                 cs_int_t  *isca,
                                 cs_real_t *blencv,
                                 cs_real_t *sigmas,
                                 cs_int_t  *iwarni,
                           const cs_int_t  *iihmpr);

void
CS_PROCF (elflux, ELFLUX) (cs_int_t *iappel);

void
CS_PROCF (elthht, ELTHHT) (cs_int_t  *mode,
                           cs_real_t *ym,
                           cs_real_t *enthal,
                           cs_real_t *temp);

void
CS_PROCF (ellecd, ELLECD) (cs_int_t *ieljou,
                           cs_int_t *ielarc,
                           cs_int_t *ielion);

void
CS_PROCF (elphyv, ELPHYV) (void);

void
CS_PROCF (eltssc, ELTSSC) (const cs_int_t  *isca,
                                 cs_real_t *smbrs);

void
CS_PROCF (elvarp, ELVARP) (cs_int_t *ieljou,
                           cs_int_t *ielarc,
                           cs_int_t *ielion,
                           cs_int_t *iihmpr);

void
CS_PROCF (elprop, ELPROP) (cs_int_t *ieljou,
                           cs_int_t *ielarc,
                           cs_int_t *ielion);

void
CS_PROCF (eliniv, ELINIV) (cs_int_t *isuite);

void
CS_PROCF (elreca, ELRECA) (cs_real_t *dt);

void
CS_PROCF (usclim_trans, UICLIM_TRANS)(cs_int_t   *icodcl,
                                      cs_real_t  *rcodcl,
                                      cs_int_t   *itypfb,
                                      cs_int_t   *izfppp,
                                      cs_int_t   *iparoi,
                                      cs_int_t   *nvarcl);

END_C_DECLS

#endif /* __CS_ELEC_MODEL_H__ */
