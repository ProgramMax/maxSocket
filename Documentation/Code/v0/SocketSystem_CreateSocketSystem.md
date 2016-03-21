# SocketSystem::CreateSocketSystem

API version: [**v0**](../v0.md)

## What is it?

Before a developer can use maxSocket they must create a [SocketSystem](SocketSystem.md) by calling **SocketSystem::CreateSocketSystem**.

## Signature

```c++
static CreateSocketSystemResults::Enum SocketSystem::CreateSocketSystem(

    std::unique_ptr< SocketSystem > & CreatedSocketSystem

) MAX_DOES_NOT_THROW;
```

## Parameters

* **CreatedSocketSystem**
    * On success, this parameter will be populated with the created SocketSystem.
	* If this parameter previously referenced a SocketSystem, that SocketSystem will be destroyed.

## Returns

* On success, returns **CreateSocketSystemResults::Success**
* On error, returns:

| Value | Description |
| --- | --- |
| **CreateSocketSystemResults::SystemIsNotReady** | when the underlying network system is not ready. A developer can try again later. |
| **CreateSocketSystemResults::NoSystemSupport** | when the OS does not meet the minimum requirements for maxSocket. |
| **CreateSocketSystemResults::LibraryError** | when there is an error in maxSocket's logic. Please notify us if you ever see a LibraryError. |
| **CreateSocketSystemResults::UnknownError** | when there is an error maxSocket is not aware of. Please notify us if you ever see an UnknownError. |

## Example

```c++
auto SocketSystem = std::unique_ptr< maxSocket::SocketSystem >{};
auto CreateSocketSystemResult = maxSocket::SocketSystem::CreateSocketSystem( SocketSystem );
if( CreateSocketSystemResult != maxSocket::CreateSocketSystemResults::Success )
{
    // error
}
```