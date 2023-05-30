# https://github.com/flashlight/text/blob/7cba9a1351eba52727bc2948a66c62cb75ca60d1/flashlight/lib/text/decoder/Utils.h
# #' @export
# EmittingModelUpdateFunc <- R6::R6Class(
#   "EmittingModelUpdateFunc",
#   public = list(
#     #' @param emissions An externalpointer to the emissions from the input to the
#     #'  autoregressive model.
#     #' @param N An int. The size of the token set emitted by the encoder for 
#     #' each time step.
#     #' @param T An int. The total number of time steps emitted by the encoder.
#     #' @param last_token_ids An int vector. The raw token ID of the last step 
#     #' for each element in the beam.
#     #' @param proposed_token_ids An int vector. The indices of the beam 
#     #' hypotheses for which the token ID at this index is being proposed.
#     #' @param previous_states A vector of externalpointers. State from the 
#     #' previous time steps for each candidate in the beam.
#     #' @param current_time_step An int. The current time step being decoded.
#     #' @returns a list(list(matrix, externalpointer))
#     initialize = function(
#       emissions,
#       N,
#       T,
#       last_token_ids,
#       proposed_token_ids,
#       previous_states,
#       current_time_step
#     ) {
#       private$emissions_ <- emissions
#       private$N_ <- N
#       private$T_ <- T
#       private$last_token_ids_ <- last_token_ids
#       private$proposed_token_ids_ <- proposed_token_ids
#       private$previous_states_ <- previous_states
#       private$current_time_step_ <- current_time_step
#       private$ptr_ <- cpp_EmittingModelUpdateFunc_constructor(
#         emissions,
#         N,
#         T,
#         last_token_ids,
#         proposed_token_ids,
#         previous_states,
#         current_time_step
#       )
#     }
#   ),
#   
#   active = list(
#     #' @field ptr set and get the pointer to a EmittingModelUpdateFunc instance.
#     ptr = function(new_ptr) {
#       if(!missing(new_ptr)) private$ptr_ <- new_ptr
#       private$ptr_
#     }
#   ),
#   
#   private = list(
#     ptr_ = NULL,
#     emissions_ = NULL,
#     N_ = NULL,
#     T_ = NULL,
#     last_token_ids_ = NULL,
#     proposed_token_ids_ = NULL,
#     previous_states_ = NULL,
#     current_time_step_ = NULL
#   )
# )


