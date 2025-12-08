#include <stdio.h>
#include "interface.h"

void cabecalho() {
    printf(GREEN"\t\t                                                                    #           \n");
    printf("\t\t                                                                    ###              \n");
    printf("\t\t                                                                    #####            \n");
    printf("\t\t                                                                    #######          \n");
    printf("\t\t                                                                    #####            \n");
    printf("\t\t                                                                    ###              \n");
    printf("\t\t                                                                    #                \n");
    printf("\t\t                                                                    #                \n");
    printf("\t\t                                                                    #                \n");

    printf("\t\t                                            "RED"*"GREEN"                     "RED"*"GREEN"                  \n");
    printf("\t\t                                           "RED"*"GREEN" "RED"*"GREEN"                   "RED"*"GREEN"                   \n");
    printf("\t\t                                          "RED"*"GREEN"   "RED"*"GREEN"                 "RED"*"GREEN"                    \n");
    printf("\t\t                                         "RED"*"GREEN"     "RED"*"GREEN"               "RED"*"GREEN"                     \n");
    printf("\t\t                                        "RED"*"GREEN"       "RED"*"GREEN"             "RED"*"GREEN"                      \n");
    printf("\t\t                                       "RED"*"GREEN"         "RED"*"GREEN"           "RED"*"GREEN"                       \n");
    printf("\t\t                          #####       "RED"*"GREEN"           "RED"*"GREEN"         "RED"*"GREEN"                        \n");
    printf("\t\t                        ##     ##    "RED"*"GREEN"             "RED"*"GREEN"       "RED"*"GREEN"                         \n");
    printf("\t\t                        ##     ##   "RED"*"GREEN"               "RED"*"GREEN"     "RED"*"GREEN"                          \n");
    printf("\t\t                          #####    "RED"*"GREEN"                 "RED"*"GREEN"   "RED"*"GREEN"                           \n");
    printf("\t\t                           ###    "RED"*"GREEN"                   "RED"*"GREEN" "RED"*"GREEN"                            \n");
    printf("\t\t                            #    "RED"*"GREEN"                     "RED"*"GREEN"                             \n");
    printf("\n");
    printf(GREEN"\t\t                         "RED"N"GREEN"AVEG"RED"A"GREEN"MAZON - GUIA TURISTICO (CENTRO DE MANAUS)\n"RESET);
}

void iconecadastrousuario() {
    printf("\t\t\t\t\t          "RESET"##########"GREEN"    ##        \n");
    printf("\t\t\t\t\t       "RESET"####             "GREEN"##        \n");
    printf("\t\t\t\t\t     "RESET"###    "RED"######   "GREEN"########     \n");
    printf("\t\t\t\t\t    "RESET"##     "RED"#      #     "GREEN"##        \n");
    printf("\t\t\t\t\t  "RESET"###     "RED"#        #    "GREEN"##        \n");
    printf("\t\t\t\t\t  "RESET"#      "RED"#          #             \n");
    printf("\t\t\t\t\t "RESET"##      "RED"#          #      "RESET"##     \n");
    printf("\t\t\t\t\t"RESET"##        "RED"#        #        "RESET"##    \n");
    printf("\t\t\t\t\t"RESET"#          "RED"#      #          "RESET"#    \n");
    printf("\t\t\t\t\t"RESET"#           "RED"######           "RESET"#    \n");
    printf("\t\t\t\t\t"RESET"#         "RED"#        #         "RESET"#    \n");
    printf("\t\t\t\t\t"RESET"#        "RED"#          #        "RESET"#    \n");
    printf("\t\t\t\t\t"RESET"##      "RED"#            #      "RESET"##    \n");
    printf("\t\t\t\t\t "RESET"##    "RED"#              #    "RESET"##     \n");
    printf("\t\t\t\t\t  "RESET"#   "RED"#                #   "RESET"#      \n");
    printf("\t\t\t\t\t  "RESET"## "RED"#                  #"RESET" ##      \n");
    printf("\t\t\t\t\t    "RESET"##                  "RESET"##        \n");
    printf("\t\t\t\t\t     "RESET"###              "RESET"###         \n");
    printf("\t\t\t\t\t       "RESET"####        "RESET"####           \n");
    printf("\t\t\t\t\t          "RESET"##########              \n");
    printf("\n");
}

void iconelogin() {
    printf("\t\t\t\t\t           ##########              \n");
    printf("\t\t\t\t\t        ####        ####           \n");
    printf("\t\t\t\t\t      ###    "RED"######    "RESET"###         \n");
    printf("\t\t\t\t\t     ##     "RED"#      #     "RESET"##        \n");
    printf("\t\t\t\t\t    ##     "RED"#        #     "RESET"###      \n");
    printf("\t\t\t\t\t          "RED"#          #      "RESET"#      \n");
    printf("\t\t\t\t\t     "GREEN"#    "RED"#          #      "RESET"##     \n");
    printf("\t\t\t\t\t      "GREEN"#    "RED"#        #        "RESET"##    \n");
    printf("\t\t\t\t\t      "GREEN"###   "RED"#      #          "RESET"#    \n");
    printf("\t\t\t\t\t"GREEN"###########  "RED"######           "RESET"#    \n");
    printf("\t\t\t\t\t      "GREEN"###  "RED"#       #         "RESET"#     \n");
    printf("\t\t\t\t\t      "GREEN"#   "RED"#          #        "RESET"#    \n");
    printf("\t\t\t\t\t     "GREEN"#   "RED"#            #      "RESET"##    \n");
    printf("\t\t\t\t\t        "RED"#              #    "RESET"##     \n");
    printf("\t\t\t\t\t       "RED"#                #   "RESET"#      \n");
    printf("\t\t\t\t\t   ###"RED"#                  #"RESET"###      \n");
    printf("\t\t\t\t\t     ##                  ##        \n");
    printf("\t\t\t\t\t      ###              ###         \n");
    printf("\t\t\t\t\t        ####        ####           \n");
    printf("\t\t\t\t\t           ##########              \n");
    printf("\n");
}

void iconeadministrador() {
    printf("\t\t\t\t\t             ##########              \n");
    printf("\t\t\t\t\t          ####        ####           \n");
    printf("\t\t\t\t\t        ###    "RED"######    "RESET"###         \n");
    printf("\t\t\t\t\t       ##     "RED"#      #     "RESET"##        \n");
    printf("\t\t\t\t\t     ###     "RED"#        #     "RESET"###      \n");
    printf("\t\t\t\t\t     #      "RED"#          #      "RESET"#      \n");
    printf("\t\t\t\t\t    ##      "RED"#          #      "RESET"##     \n");
    printf("\t\t\t\t\t   ##        "RED"#        #        "RESET"##    \n");
    printf("\t\t\t\t\t   #          "RED"#      #          "RESET"#    \n");
    printf("\t\t\t\t\t   #           "RED"######           "RESET"#    \n");
    printf("\t\t\t\t\t             "RED"#        #         "RESET"#    \n");
    printf("\t\t\t\t\t      "GREEN"###   "RED"#          #        "RESET"#    \n");
    printf("\t\t\t\t\t     "GREEN"#   #              "RED"#      "RESET"##    \n");
    printf("\t\t\t\t\t    "GREEN"#     ###########     "RED"#    "RESET"##    \n");
    printf("\t\t\t\t\t     "GREEN"#   #      # #        "RED"#   "RESET"#     \n");
    printf("\t\t\t\t\t      "GREEN"###       # #         "RED"#"RESET"##      \n");
    printf("\t\t\t\t\t                           ##        \n");
    printf("\t\t\t\t\t        ###              ###         \n");
    printf("\t\t\t\t\t          ####        ####           \n");
    printf("\t\t\t\t\t             ##########              \n");
    printf("\n");
}

void iconelistar() {
    printf("\t\t\t\t\t         "GREEN"########################            \n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"##                  "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"## ______________   "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"##                  "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"## ______________   "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"##                  "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"## ______________   "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"##                  "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"## ______________   "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"########################            \n");
    printf("\n");
}

void iconefiltrar() {
    printf("\t\t\t\t\t                      "GREEN"##########    \n");
    printf("\t\t\t\t\t                      "GREEN"# "RED"______ "GREEN"#    \n");
    printf("\t\t\t\t\t                      "GREEN"# "RED"______ "GREEN"#    \n");
    printf("\t\t\t\t\t                      "GREEN"# "RED"______ "GREEN"#    \n");
    printf("\t\t\t\t\t                      "GREEN"#        "GREEN"#"RESET"    \n");
    printf("\t\t\t\t\t                    ##############  \n");
    printf("\t\t\t\t\t                     #          #   \n");
    printf("\t\t\t\t\t                      #        #    \n");
    printf("\t\t\t\t\t                       #      #     \n");
    printf("\t\t\t\t\t                        #    #      \n");
    printf("\t\t\t\t\t                         #  #       \n");
    printf("\t\t\t\t\t                         #  #       \n");
    printf("\t\t\t\t\t                         # /        \n");
    printf("\t\t\t\t\t                         #          \n");
    printf("\n");
}

void iconecomentarios() {
    printf("\t\t\t\t\t             "GREEN"###########    \n");
    printf("\t\t\t\t\t           "GREEN"#  "RED"________  "GREEN"#   \n");
    printf("\t\t\t\t\t          "GREEN"#   "RED"________   "GREEN"#  \n");
    printf("\t\t\t\t\t         "GREEN"#    "RED"________    "GREEN"# \n");
    printf("\t\t\t\t\t         "GREEN"#    "RED"________    "GREEN"# \n");
    printf("\t\t\t\t\t          "GREEN"#   "RED"________   "GREEN"#  \n");
    printf("\t\t\t\t\t           "GREEN"#            #   \n");
    printf("\t\t\t\t\t            "GREEN"#   ########    \n");
    printf("\t\t\t\t\t             "GREEN"#  #           \n");
    printf("\t\t\t\t\t              "GREEN"##            \n");
    printf("\t\t\t\t\t               "GREEN"#            \n");
    printf("\n");
}
