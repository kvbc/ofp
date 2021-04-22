@page getting_started Getting started

The following diagram shows the relation between modules and the flow of information between them.

<!-- 50% size -->
@image{inline} html infoflow.png width=750 height=670

- - -

# Arguments

Arguments included in @ref ofp_state_s.udal (**UDAL**) are called **UDA** (User-Defined Argument),  
but arguments inputted in the command-line are called **UIA** (User-Inputed Argument).

- - -

# Options

Options are either [Double-UIA](argument_8h.html#af82303803d7ccdedb90b343ba5316a59aacf611661ed01b51ba6328e589e6f1da) (**DUIA**)
or [Single-UIA](argument_8h.html#af82303803d7ccdedb90b343ba5316a59a1fc4a8c449a1d725043d6abc7f64847f) (**SUIA**).

**DUIA** options consist of two UIA, first one is the UDA identifier and the second one is the UDA value.
> `/option value`

**SUIA** options consist of one UIA, including the UDA identifier and the UDA value.
> `/optionvalue`

- - -

# State

The OFP state contains 3 major argument lists.
  - [UDA List](structofp__state__s.html#a071aef17eb16bbe0d157226e94764ab9) (**UDAL**)
    - User-Defined Argument List is being filled by the ::ofp_argument_register function
  - [Unknown UIA List](structofp__state__s.html#a23da6f10439a676b12fa04ce189b89a6) (**UUIAL**)
    - Unknown User-Inputted Argument List contains undefined UIA
  - [Non-Argument List](structofp__state__s.html#ae433476a606294aac88275d4cef7658f) (**NAL**)
    - Non-Argument List contains UIA not starting with the specified [prefix](structofp__state__s.html#a33937ce854d969715331caec715cce1e)