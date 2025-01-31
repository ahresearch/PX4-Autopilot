############################################################################
#
#   Copyright (c) 2016 PX4 Development Team. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name PX4 nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################

px4_add_module(
	MODULE modules__logger_backup
	MAIN logger_backup
	PRIORITY "SCHED_PRIORITY_MAX-30"
	COMPILE_FLAGS
		${MAX_CUSTOM_OPT_LEVEL}
		-Wno-cast-align # TODO: fix and enable
	SRCS
		logger_backup.cpp
	DEPENDS
	        DYNAMIC
		version
	)

target_compile_definitions(modules__logger_backup
        PUBLIC
                PX4_BOARD_NAME="${PX4_BOARD_NAME}"
                PX4_BOARD_LABEL="${PX4_BOARD_LABEL}"
        )


target_include_directories(modules__logger_backup PUBLIC  ../../../../../bitsery/include ../logger)
target_link_libraries(modules__logger_backup PRIVATE git_ver)
target_link_libraries(modules__logger_backup PRIVATE drivers_board)
target_link_libraries(modules__logger_backup PUBLIC uORB modules__logger)

